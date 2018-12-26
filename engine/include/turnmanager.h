#ifndef _TURN_MANAGER_H_
#define _TURN_MANAGER_H_

#include "gamestate.h"
#include <memory>

namespace l5r
{
   class turnManager
   {
      public:
         turnManager(std::shared_ptr<gamestate> state);
         ~turnManager();

         void setCurrentTurnAndAction(int playerNum);
         bool ActionAndTurnDiffer();
         void setActionToCurrentTurn();

         void swapAction();

      private:
         std::shared_ptr<gamestate> state;
   };
};
#endif // _TURN_MANAGER_H_