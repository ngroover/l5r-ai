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

         // decision functions
         decision strongholdDecision();
         decision dynastyMulliganDecision();
         decision conflictMulliganDecision();

         // action functions
         void doStrongholdSelection(choice c);
         void doDynastyMulligan(choice c);
         void doConflictMulligan(choice c);

         // support functions
         void shiftProvinceRow();
         void placeDynastyCards(std::string playerName, playercards &gameCards);
         void drawConflictCards(std::string playerName, playercards &gameCards);

         bool discardDynastyMulligans();
         void replaceDynastyMulligans();

         void gainHonor(std::string playerName, playercards &gameCards);

         // dynasty phase setup
         void flipProvinceCards(std::string playerName, playercards &gameCards);
         void gainFate(std::string playerName, playercards &gameCards);
   };
}

#endif //_PREGAME_ENGINE_H_
