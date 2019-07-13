#ifndef _CONFLICT_RESOLUTION_MANAGER_H_
#define _CONFLICT_RESOLUTION_MANAGER_H_

#include <memory>
#include "card.h"

namespace l5r
{
   class cardarea;
   class conflictPlayerState;
   class conflictState;
   class GameStateIntfc;
   class cardDataManager;
   enum class conflictwinner
   {
      attacker,
      defender,
      nobody
   };

   class ConflictResult
   {
      public:
         conflictwinner winner;
         bool unopposed;
         bool brokeProvince;
   };

   class ConflictResolutionManager
   {
      public:
         ConflictResolutionManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr);
         ~ConflictResolutionManager();
         
         ConflictResult resolveConflict();

      private:
         int findHoldingBonus();
         void breakProvince(cardarea *cards, CardSharedPtr cardIndex);
         int calculateStr(conflictPlayerState *player);

         cardarea *attacker, *defender;
         conflictPlayerState *attackerState, *defenderState;
         conflictState *global;
         std::shared_ptr<GameStateIntfc> stateIntfc;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};
#endif // _CONFLICT_RESOLUTION_MANAGER_H_
