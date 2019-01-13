#include "engine.h"
#include <random>
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>

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
   phaseMgr = std::make_shared<phaseManager>(state, dynastyMgr, conflictMgr, provinceMgr, turnMgr, tokenMgr, agentMgr, cardDataMgr);

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

   std::cout << "First player is " << agentMgr->getPlayerName(1) << std::endl;
   turnMgr->setCurrentTurnAndAction(1);

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

gamestate engine::getGameState()
{
   return *state;
}

void engine::setGameState(gamestate &gs)
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

void engine::run()
{
   while( state->currentPhase != phase::gameover )
   {
      decision d = getDecision();
      choice c = agentMgr->getCurrentPlayerChoice(d);
      doAction(c);
   }
}
