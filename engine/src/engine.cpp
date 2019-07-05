#include "engine.h"
#include <random>
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "gamestateintfc.h"
#include "cardareamanager.h"

using namespace l5r;

// constructor
engine::engine(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2): player1(std::move(player1)), player2(std::move(player2))
{
   state = std::make_shared<gamestate>();

   stateIntfc = std::make_shared<GameStateIntfc>(state, this->player1->getName(), this->player2->getName());

   // initialize managers
   cardDataMgr = std::make_shared<cardDataManager>(state);
   dynastyMgr = std::make_shared<dynastyCardManager>(state, cardDataMgr);
   turnMgr = std::make_shared<turnManager>(state);
   provinceMgr = std::make_shared<provinceCardManager>(state, cardDataMgr);
   phaseMgr = std::make_shared<phaseManager>(state, dynastyMgr, provinceMgr, turnMgr, cardDataMgr, stateIntfc);

   // setup the gamestate
   std::cout << "Setting up game:" << std::endl;
   std::cout << this->player1->getName() << " (" << this->player1->getDeckList().getName() << ")" <<std::endl;
   std::cout << this->player2->getName() << " (" << this->player2->getDeckList().getName() << ")" <<std::endl;

   std::cout << "First player is " << this->player1->getName() << std::endl;
   turnMgr->setCurrentTurnAndAction(1);

   cardDataMgr->loadDecklist(this->player1->getDeckList());
   cardDataMgr->loadDecklist(this->player2->getDeckList());
   CardAreaManager player1Cards(stateIntfc->getPlayerCards(), this->player1->getName(), cardDataMgr);
   CardAreaManager player2Cards(stateIntfc->getOpponentCards(), this->player2->getName(), cardDataMgr);

   player1Cards.setupCards(this->player1->getDeckList(), state->cardIds);
   player2Cards.setupCards(this->player2->getDeckList(), state->cardIds);

   // select stronghold is the first player decision
   phaseMgr->goToStrongholdSelection();
}

// destructor
engine::~engine()
{
}

decision engine::getDecision()
{
   return phaseMgr->getDecision();
}

gamestate &engine::getGameState()
{
   return *state;
}

void engine::setGameState(gamestate gs)
{
   *state = gs;
}

void engine::doAction(choice c)
{
   phaseMgr->doAction(c);
   decision d;
   do
   {
      d = phaseMgr->getDecision();
      if( state->currentPhase != phase::gameover )
      {
         // if theres only 1 choice do it and keep going
         if(d.getChoiceList().size() == 1)
         {
            doAction(*d.getChoiceList().begin());
         }
         // feed in a none choice if theres no choices
         if(d.getChoiceList().size() == 0)
         {
            choice c("", choicetype::none);
            doAction(c);
         }
      }
   } while(d.getChoiceList().size() <= 1 && state->currentPhase != phase::gameover);
}

void engine::run(bool debug)
{
   std::ofstream debugfile;
   debugfile.open("debug_choices.txt");
   while( state->currentPhase != phase::gameover )
   {
      decision d = getDecision();
      if( state->currentAction == player::player1 )
      {
         choice c = player1->chooseAction(d);
         if(debug)
         {
            debugfile << player1->getName() << ": " << c.getText() << std::endl;
         }
         doAction(c);
      }
      else
      {
         choice c = player2->chooseAction(d);
         if(debug)
         {
            debugfile << player2->getName() << ": " << c.getText() << std::endl;
         }
         doAction(c);
      }
   }
}
