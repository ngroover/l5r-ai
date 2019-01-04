#ifndef _PROVINCE_CARD_MANAGER_H_
#define _PROVINCE_CARD_MANAGER_H_

#include "state/gamestate.h"
#include "carddatamanager.h"
#include "agentmanager.h"
#include "choice.h"


namespace l5r
{
   class provinceCardManager
   {
      public:
         provinceCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr,std::shared_ptr<agentManager> agentMgr);
         ~provinceCardManager();

         void createDeck(decklist deck, int playerNum);

         // chooses a stronghold for the currently active player
         void chooseStronghold(int provinceChoice);

         void breakProvince(playerstate &pState, int cardIndex);
         int getStartingHonor(int playerNum);

         std::list<choice> getStrongholdChoices();

         std::list<choice> getProvinceChoices(playerstate &pState);

         int getStrongholdProvince(playerstate &pState);

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
         std::shared_ptr<agentManager> agentMgr;
   };
};
#endif // _PROVINCE_CARD_MANAGER_H_
