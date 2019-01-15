#ifndef _PROVINCE_CARD_MANAGER_H_
#define _PROVINCE_CARD_MANAGER_H_

#include "state/gamestate.h"
#include "carddatamanager.h"
#include "choice.h"


namespace l5r
{
   class cardarea;
   class provinceCardManager
   {
      public:
         provinceCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr);
         ~provinceCardManager();

         // chooses a stronghold for the currently active player
         void chooseStronghold(cardarea *cards, int provinceChoice);

         void breakProvince(cardarea *cards, int cardIndex);
         int getStartingHonor(cardarea *cards);

         std::list<choice> getStrongholdChoices(cardarea *cards);

         std::list<choice> getProvinceChoices(cardarea *cards);

         int getStrongholdProvince(cardarea *cards);

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};
#endif // _PROVINCE_CARD_MANAGER_H_
