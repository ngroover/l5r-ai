#ifndef _PHASE_MANAGER_H_
#define _PHASE_MANAGER_H_

#include "gamestate.h"
#include <memory>
#include "dynastycardmanager.h"
#include "conflictcardmanager.h"
#include "provincecardmanager.h"
#include "turnmanager.h"
#include "tokenmanager.h"
#include "ringmanager.h"
#include "agentmanager.h"
#include "choice.h"
#include "decision.h"

namespace l5r
{
   class phaseManager
   {
      public:
         phaseManager(std::shared_ptr<gamestate> state, std::shared_ptr<dynastyCardManager> dynastyMgr,std::shared_ptr<conflictCardManager> conflictMgr, std::shared_ptr<provinceCardManager> provinceMgr, std::shared_ptr<turnManager> turnMgr, std::shared_ptr<tokenManager> tokenMgr, std::shared_ptr<ringManager> ringMgr, std::shared_ptr<agentManager> agentMgr);
         ~phaseManager();


         void doAction(choice c);

         decision getDecision();

         // TODO: move to constructor and delete
         void goToStrongholdSelection();

      private:
         void goToDynastyMulligan();
         void goToConflictMulligan();
         void goToAdditionalFate();
         void goToProvincePlay();
         void doDynastyEntry();
         void doDrawPhaseEntry();

         // pregame actions
         void pregameDoAction(choice c);
         void dynastyDoAction(choice c);
         void drawDoAction(choice c);
         void doStrongholdSelection(choice c);
         void doDynastyMulligan(choice c);
         void doConflictMulligan(choice c);
         void doBid(choice c);

         // dynasty actions
         void doProvincePlayAction(choice c);
         void doAdditionalFate(choice c);
         
         // pregame choices
         decision getPreGameDecision();
         decision getDynastyDecision();
         decision getStrongholdDecision();
         decision getDynastyMulliganDecision();
         decision getConflictMulliganDecision();
         decision getProvincePlayDecision();
         decision getAdditionalFateDecision();
         decision getDrawDecision();
         decision getBidDecision();

         // dynasty choices

         std::shared_ptr<gamestate> state;

         std::shared_ptr<dynastyCardManager> dynastyMgr;
         std::shared_ptr<conflictCardManager> conflictMgr;
         std::shared_ptr<provinceCardManager> provinceMgr;
         std::shared_ptr<turnManager> turnMgr;
         std::shared_ptr<tokenManager> tokenMgr;
         std::shared_ptr<ringManager> ringMgr;
         std::shared_ptr<agentManager> agentMgr;
   };
}

#endif //_PHASE_MANAGER_H_
