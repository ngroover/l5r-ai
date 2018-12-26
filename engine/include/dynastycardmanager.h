#ifndef _DYNASTY_CARD_MANAGER_H_
#define _DYNASTY_CARD_MANAGER_H_

#include "gamestate.h"
#include "decklist.h"
#include "carddatamanager.h"
#include "agentmanager.h"
#include "choice.h"

namespace l5r
{
   enum class dynastyCardStatus
   {
      facedown,
      faceup,
      either
   };

   class dynastyCardManager
   {
      public:
         dynastyCardManager(std::shared_ptr<gamestate> state,std::shared_ptr<cardDataManager> cardMgr, std::shared_ptr<agentManager> agentMgr);
         ~dynastyCardManager();

         void createDeck(decklist deck, int playerNum);

         // fills in provinces for the specified player
         void fillProvinces(playerstate &pState, std::string playerName);

         // flip all Dynasty cards faceup
         void flipAllDynastyFaceup(playerstate &pState, std::string playerName);

         // sets aside a mulligan dynasty card
         void chooseMulliganCard(int cardChoice);
         
         void chooseCharacterToPlay(playerstate &pState, int cardChoice);

         // performs the dynasty mulligan
         void performMulligan();

         // get choices
         std::list<choice> getProvinceDynastyChoices(dynastyCardStatus dcs);

         // get choices with fate cost or less
         std::list<choice> getProvinceDynastyChoicesWithFate(dynastyCardStatus dcs, int fateCost);

         // get pending dynasty card
         int getPendingFateCard(playerstate &pState);

         // play pending character
         void playCharacter(playerstate &pState, std::string playerName);

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
         std::shared_ptr<agentManager> agentMgr;
   };
}

#endif //_DYNASTY_CARD_MANAGER_H_
