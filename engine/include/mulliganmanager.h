#ifndef _MULLIGAN_MANAGER_H_
#define _MULLIGAN_MANAGER_H_

#include <string>
#include <list>
#include <memory>
#include "choice.h"

namespace l5r
{
   class cardarea;
   class cardDataManager;
   class MulliganManager
   {
      public:
         MulliganManager(cardarea *cards, std::string name, std::shared_ptr<cardDataManager> cardMgr);
         ~MulliganManager();

         void chooseDynastyMulligan(CardSharedPtr cardChoice);
         void performDynastyMulligan();
         std::list<choice> getDynastyMulliganChoices();

         void chooseConflictMulligan(CardSharedPtr cardChoice);
         void performConflictMulligan();
         std::list<choice> getConflictMulliganChoices();

      private:
         cardarea *cards;
         std::string name;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};

#endif // _MULLIGAN_MANAGER_H_
