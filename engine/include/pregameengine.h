#ifndef _PREGAME_ENGINE_H_
#define _PREGAME_ENGINE_H_

#include "engineshared.h"
#include "choice.h"
#include <memory>


namespace l5r
{
   class pregameEngine
   {
      public:
         pregameEngine(std::shared_ptr<engineShared> es);
         ~pregameEngine();

         decision getDecision();

         void doAction(choice c);
      private:
         std::shared_ptr<engineShared> shared;
   };
}

#endif //_PREGAME_ENGINE_H_
