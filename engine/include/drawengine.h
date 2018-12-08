#ifndef _DRAW_ENGINE_H_
#define _DRAW_ENGINE_H_

#include "engineshared.h"
#include "choice.h"
#include <memory>

namespace l5r
{
   class drawEngine
   {
      public:
         drawEngine(std::shared_ptr<engineShared> es);
         ~drawEngine();

         decision getDecision();

         void doAction(choice c);
      private:
         std::shared_ptr<engineShared> shared;

         decision getBidDecision();

         void doBid(choice c);

         // support functions
         void exchangeHonor(std::string name, playercards &gameCards, playercards &opponentCards);
         void drawCards(std::string name, playercards &gameCards, int num);
   };
}

#endif //_DRAW_ENGINE_H_
