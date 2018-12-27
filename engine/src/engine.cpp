#include "engine.h"
#include <random>
#include <iostream>
#include <memory>
#include <sstream>

using namespace l5r;

// constructor
engine::engine(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2)
{
   state = std::make_shared<gamestate>();

   // initialize managers
   agentMgr = std::make_shared<agentManager>(std::move(player1),std::move(player2),state);
   cardDataMgr = std::make_shared<cardDataManager>(state);
   dynastyMgr = std::make_shared<dynastyCardManager>(state, cardDataMgr, agentMgr);
   turnMgr = std::make_shared<turnManager>(state);
   conflictMgr = std::make_shared<conflictCardManager>(state, cardDataMgr, agentMgr);
   provinceMgr = std::make_shared<provinceCardManager>(state, cardDataMgr, agentMgr);
   tokenMgr = std::make_shared<tokenManager>(state, cardDataMgr);
   ringMgr = std::make_shared<ringManager>(state);
   conflictDataMgr = std::make_shared<conflictManager>(state, cardDataMgr);
   phaseMgr = std::make_shared<phaseManager>(state, dynastyMgr, conflictMgr, provinceMgr, turnMgr, tokenMgr, ringMgr,agentMgr,conflictDataMgr);

   // setup the gamestate
   std::cout << "Setting up game:" << std::endl;
   for(int i=1;i<=2;i++)
   {
      std::cout << agentMgr->getPlayerName(i) << " (" << agentMgr->getPlayerDecklist(i).getName() << ")" <<std::endl;
      cardDataMgr->loadDecklist(agentMgr->getPlayerDecklist(i), i);
      dynastyMgr->createDeck(agentMgr->getPlayerDecklist(i), i);
      conflictMgr->createDeck(agentMgr->getPlayerDecklist(i), i);
      provinceMgr->createDeck(agentMgr->getPlayerDecklist(i), i);
   }

   // randomly determine first player
   std::random_device rd;
   std::mt19937 gen(rd());

   std::uniform_int_distribution<int> d(1,2);
   int choice = d(gen);
   if( choice == 1 || choice == 2 )
   {
      std::cout << "First player is " << agentMgr->getPlayerName(choice) << std::endl;
      turnMgr->setCurrentTurnAndAction(choice);
   }
   else
   {
      std::stringstream ss;
      ss << choice;
      std::string strChoice;
      ss >> strChoice;
      strChoice = "Invalid random choice" + strChoice;
      throw std::runtime_error(strChoice.c_str());
   }

   // select stronghold is the first player decision
   phaseMgr->goToStrongholdSelection();


}

// destructor
engine::~engine()
{
}

decision engine::getDecision()
{
   decision d;
   do
   {
      d = phaseMgr->getDecision();
      // if theres only 1 choice do it and keep going
      if(d.getChoiceList().size() == 1)
      {
         doAction(*d.getChoiceList().begin());
      }
   } while(d.getChoiceList().size() == 1);
   return d;
}

std::shared_ptr<gamestate> engine::getGameState()
{
   return state;
}

void engine::doAction(choice c)
{
   phaseMgr->doAction(c);
}


void engine::run()
{
   while( state->currentPhase != phase::gameover )
   {
      decision d = getDecision();
      choice c = agentMgr->getCurrentPlayerChoice(d);
      doAction(c);
   }
}
