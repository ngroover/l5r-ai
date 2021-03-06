#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "state/gamestate.h"
#include <action.h>
#include <list>
#include <map>
#include <memory>
#include "agent.h"
#include "dynastycardmanager.h"
#include "conflictcardmanager.h"
#include "provincecardmanager.h"
#include "carddatamanager.h"
#include "turnmanager.h"
#include "phasemanager.h"


namespace l5r
{
   class GameStateIntfc;
   class engine
   {
      public:
         engine(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2);
         ~engine();

         // useful for testing
         gamestate getGameState();

         void setGameState(gamestate gs);

         decision getDecision();

         void doAction(choice c);

         void run(bool debug);

      private:
         // shared state
         std::shared_ptr<gamestate> state;
         std::shared_ptr<GameStateIntfc> stateIntfc;

         // state managers
         std::shared_ptr<dynastyCardManager> dynastyMgr;
         std::shared_ptr<provinceCardManager> provinceMgr;
         std::shared_ptr<turnManager> turnMgr;
         std::shared_ptr<phaseManager> phaseMgr;
         std::shared_ptr<cardDataManager> cardDataMgr;

         std::unique_ptr<agent> player1,player2;
   };
};

#endif //_ENGINE_H_
