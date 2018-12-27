#ifndef _RING_MANAGER_H_
#define _RING_MANAGER_H_

#include "gamestate.h"
#include "choice.h"
#include <memory>

namespace l5r
{
   class ringManager
   {
      public:
         ringManager(std::shared_ptr<gamestate> state);
         ~ringManager();

         void setAllUnclaimed();

         std::list<choice> getConflictChoices(playerstate &pState);

         void initializeConflicts(playerstate &pState);

         void chooseConflictType(conflicttype type);
         void chooseConflictRing(ring r);

         std::string getConflictTypeName(conflicttype type);

         std::list<choice> getConflictRingChoices();

         std::string getRingName(ring r);

         void printCurrentConflict(std::string playerName);
      private:
         std::shared_ptr<gamestate> state;
   };
};
#endif // _RING_MANAGER_H_
