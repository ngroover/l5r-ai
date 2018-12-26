#ifndef _RING_MANAGER_H_
#define _RING_MANAGER_H_

#include "gamestate.h"
#include <memory>

namespace l5r
{
   class ringManager
   {
      public:
         ringManager(std::shared_ptr<gamestate> state);
         ~ringManager();

         void setAllUnclaimed();

      private:
         std::shared_ptr<gamestate> state;
   };
};
#endif // _RING_MANAGER_H_
