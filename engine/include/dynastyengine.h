#ifndef _DYNASTY_ENGINE_H
#define _DYNASTY_ENGINE_H

#include "engineshared.h"
#include "choice.h"
#include <memory>

namespace l5r
{
   class dynastyEngine
   {
      public:
         dynastyEngine(std::shared_ptr<engineShared> es);
         ~dynastyEngine();

         decision getDecision();

         void doAction(choice c);
      private:
         std::shared_ptr<engineShared> shared;

         // decision functions
         decision provincePlayDecision();
         decision additionalFateDecision();

         // action functions
         void doDynastySetup();
         void doProvincePlay(choice c);
         void doAdditionalFate(choice c);

         // support functions
         void flipProvinceCards(std::string playerName, playercards &gameCards);
         void gainFate(std::string playerName, playercards &gameCards);
   };
}

#endif //_DYNASTY_ENGINE_H
