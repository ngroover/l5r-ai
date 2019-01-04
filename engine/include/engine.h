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
#include "agentmanager.h"
#include "tokenmanager.h"
#include "conflictmanager.h"


namespace l5r
{
   class engine
   {
      public:
         engine(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2);
         ~engine();

         // useful for testing
         gamestate getGameState();

         void setGameState(gamestate &gs);

         decision getDecision();

         void doAction(choice c);

         void run();

      private:

         // shared state
         std::shared_ptr<gamestate> state;

         // state managers
         std::shared_ptr<dynastyCardManager> dynastyMgr;
         std::shared_ptr<conflictCardManager> conflictMgr;
         std::shared_ptr<provinceCardManager> provinceMgr;
         std::shared_ptr<turnManager> turnMgr;
         std::shared_ptr<phaseManager> phaseMgr;
         std::shared_ptr<agentManager> agentMgr;
         std::shared_ptr<cardDataManager> cardDataMgr;
         std::shared_ptr<tokenManager> tokenMgr;
   };
};

#endif //_ENGINE_H_
