#ifndef _CONFLICT_PHASE_MANAGER_H_
#define _CONFLICT_PHASE_MANAGER_H_

#include <memory>
#include "decision.h"

namespace l5r
{
   class GameStateIntfc;
   class cardDataManager;
   class conflictPlayerState;
   class ConflictPhaseManager
   {
      public:
         ConflictPhaseManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr);
         ~ConflictPhaseManager();

         decision getAttackersDecision();
         decision getConflictTypeDecision();
         decision getRingDecision();
         decision getAttackProvinceDecision();
         decision getDefendersDecision();
         decision getFavorDecision();

         void doChooseAttackers(choice c);
         void doChooseConflictType(choice c);
         void doChooseRing(choice c);
         void doChooseProvince(choice c);
         void doChooseDefenders(choice c);
         void doChooseFavor(choice c);

      private:
         void processEndConflict();
         void printParticipating(conflictPlayerState *cps);

         std::shared_ptr<GameStateIntfc> stateIntfc;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};

#endif // _CONFLICT_PHASE_MANAGER_H_
