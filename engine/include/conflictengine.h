#ifndef _CONFLICT_ENGINE_H_
#define _CONFLICT_ENGINE_H_

#include "engineshared.h"
#include "choice.h"
#include <memory>

namespace l5r
{
   class conflictEngine
   {
      public:
         conflictEngine(std::shared_ptr<engineShared> es);
         ~conflictEngine();

         decision getDecision();

         void doAction(choice c);
      private:
         std::shared_ptr<engineShared> shared;

         void doChooseAttackers(choice c);
         decision getAttackersDecision();

         void doChooseRing(choice c);
         decision getRingDecision();

         void doChooseConflictType(choice c);
         decision getConflictTypeDecision();

         void doChooseProvince(choice c);
         decision getProvinceDecision();

         void doChooseDefenders(choice c);
         decision getDefendersDecision();
   };
}

#endif //_CONFLICT_ENGINE_H_
