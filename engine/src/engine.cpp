#include "engine.h"
#include <random>
#include <iostream>
#include <memory>

using namespace l5r;

// constructor
engine::engine(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2)
{
   shared = std::make_shared<engineShared>();

   shared->player1 = std::move(player1);
   shared->player2 = std::move(player2);

   std::cout << "Setting up game:" << std::endl;
   std::cout << shared->player1->getName() << " (" << shared->player1->getDeckList().getName() << ")" <<std::endl;
   std::cout << shared->player2->getName() << " (" << shared->player2->getDeckList().getName() << ")" <<std::endl;

   // randomly determine first player
   std::random_device rd;
   std::mt19937 gen(rd());

   std::uniform_int_distribution<int> d(1,2);
   int choice = d(gen);
   if( choice == 1 )
   {
      std::cout << "First player is " << shared->player1->getName() << std::endl;
      shared->state.currentAction = player::player1;
      shared->state.currentTurn =  player::player1;
   }
   else
   {
      std::cout << "First player is " << shared->player2->getName() << std::endl;
      shared->state.currentAction = player::player2;
      shared->state.currentTurn =  player::player2;
   }

   // select stronghold is the first player decision
   shared->state.currentPhase = phase::pregame;
   shared->state.currentSubPhase = subphase::stronghold_selection;

   // TODO: Validate the decklists
   std::map<cards,card> list1 = populateCards(shared->player1, shared->state.player1Cards);
   std::map<cards,card> list2 = populateCards(shared->player2, shared->state.player2Cards);

   shared->cardList = list1;

   // merge card info
   for( auto const c : list2 )
   {
      if ( shared->cardList.find(c.first) == shared->cardList.end() )
      {
         shared->cardList.insert(std::pair<cards,card>(c.first,c.second));
      }
   }

   // initialize engine subsystems
   pregame = std::make_unique<pregameEngine>(shared);
}

// destructor
engine::~engine()
{
}

std::map<cards,card> engine::populateCards(std::unique_ptr<agent> &player, playercards &gameCards)
{
   // get cards and put them into the gamestate
   std::map<cards,card> tmpList = cg.generateCards(player->getDeckList());
   int provinceSlot=0;

   for(auto c : tmpList )
   {
      if ( c.second.getType() == cardtype::stronghold )
      {
         gameCards.stronghold = c.first;
      }
      else if ( c.second.getType() == cardtype::province )
      {
         gameCards.province[provinceSlot++] = c.first;
      }
      else if (c.second.getType() == cardtype::dynasty )
      {
         gameCards.dynasty_drawdeck.push_back(c.first);
      }
      else if (c.second.getType() == cardtype::conflict )
      {
         gameCards.conflict_drawdeck.push_back(c.first);
      }
   }

   return tmpList;
}

void engine::setGameState(gamestate gs)
{
   shared->state = gs;
}

decision engine::getDecision()
{
   switch(shared->state.currentPhase)
   {
      case phase::pregame:
         return pregame->getDecision();
      default:
         throw "Invalid phase";
   }
}

gamestate engine::getGameState()
{
   return shared->state;
}

void engine::doAction(choice c)
{
   switch(shared->state.currentPhase)
   {
      case phase::pregame:
         pregame->doAction(c);
         break;
      default:
         throw "Invalid phase";
   }
}


void engine::run()
{
   while( shared->state.currentPhase != phase::gameover )
   {
      decision d = getDecision();
      choice c = shared->getCurrentPlayer()->chooseAction(d);
      doAction(c);
   }
}
