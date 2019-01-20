#ifndef _IMPERIAL_FAVOR_MANAGER_H_
#define _IMPERIAL_FAVOR_MANAGER_H_

#include <memory>
#include "state/conflict.h"

namespace l5r
{
   enum class favorwinner
   {
      attacker,
      defender,
      neither
   };

   class GameStateIntfc;
   class cardDataManager;
   class cardarea;
   class ImperialFavorManager
   {
      public:
         ImperialFavorManager(std::shared_ptr<GameStateIntfc> stateIntfc,
            std::shared_ptr<cardDataManager> cardMgr);
         ~ImperialFavorManager();

         void initializeFavor();
         void changeFavorType(conflicttype newtype);

         favorwinner calculateWinner();

      private:
         int countFavorGlory(cardarea *cards);

         cardarea *attacker, *defender;
         conflictPlayerState *attackerState, *defenderState;
         conflictState *global;
         std::shared_ptr<GameStateIntfc> stateIntfc;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};
#endif // _IMPERIAL_FAVOR_MANAGER_H_
