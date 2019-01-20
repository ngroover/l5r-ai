#ifndef _RING_MANAGER_H_
#define _RING_MANAGER_H_

#include <memory>
#include <string>
#include "state/ring.h"

namespace l5r
{
   class GameStateIntfc;
   class cardDataManager;

   class RingManager
   {
      public:
         RingManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr);
         ~RingManager();

         void initialize();

         // TODO move to conflict manager
         void initializeConflicts();

         void unclaimRings();

         void putFateOnRings();

      private:
         std::shared_ptr<GameStateIntfc> stateIntfc;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};

#endif // _RING_MANAGER_H_
