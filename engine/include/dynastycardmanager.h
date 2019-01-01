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

         inplaycharacter removeCharacterFromHome(playerstate &pState, int cardChoice);

         // performs the dynasty mulligan
         void performMulligan();

         // get choices
         std::list<choice> getProvinceDynastyChoices(dynastyCardStatus dcs);

         // get choices with fate cost or less
         std::list<choice> getProvinceDynastyChoicesWithFateCost(dynastyCardStatus dcs, int fateCost);

         // get pending dynasty card
         int getPendingFateCard(playerstate &pState);

         // play pending character
         void playCharacter(playerstate &pState, std::string playerName, int extraFate);

         // get characters that can attack
         std::list<choice> getAttackerChoices(playerstate &pState);

         // get characters that can defend
         std::list<choice> getDefenderChoices(playerstate &pState);

         int conflictTotal(playerstate &pState);

         void sendCharactersHome(std::list<inplaycharacter> charlist, playerstate &pState);

         int countFavorGlory(playerstate &pState);

         std::list<choice> getCharactersWithNoFate();

         void discardCharacter(int cardIndex);

         void removeFateFromCharacters();

         void discardProvinceCard(int cardIndex);
         
         void readyAllCharacters();

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
         std::shared_ptr<agentManager> agentMgr;
   };
}

#endif //_DYNASTY_CARD_MANAGER_H_
