#ifndef _DYNASTY_CARD_MANAGER_H_
#define _DYNASTY_CARD_MANAGER_H_

#include "state/gamestate.h"
#include "decklist.h"
#include "carddatamanager.h"
#include "choice.h"

namespace l5r
{
   enum class dynastyCardStatus
   {
      facedown,
      faceup,
      either
   };

   class cardarea;
   class tokenManager;

   class dynastyCardManager
   {
      public:
         dynastyCardManager(std::shared_ptr<gamestate> state,std::shared_ptr<cardDataManager> cardMgr);
         ~dynastyCardManager();

         // fills in provinces for the specified player
         void fillProvinces(cardarea *cards, tokenManager *tokens, std::string playerName);

         // flip all Dynasty cards faceup
         void flipAllDynastyFaceup(cardarea *cards, std::string playerName);

         // sets aside a mulligan dynasty card
         
         void chooseCharacterToPlay(cardarea *cards, int cardChoice);

         inplaycharacter removeCharacterFromHome(cardarea *cards, int cardChoice);

         // performs the dynasty mulligan

         // get choices with fate cost or less
         std::list<choice> getProvinceDynastyChoicesWithFateCost(cardarea *cards, dynastyCardStatus dcs, int fateCost);

         // get pending dynasty card
         int getPendingFateCard(cardarea *cards);

         // play pending character
         void playCharacter(cardarea *cards, std::string playerName, int extraFate);

         int getPendingCharCost(cardarea *cards);

         // get characters that can attack
         std::list<choice> getAttackerChoices(cardarea *cards);

         // get characters that can defend
         std::list<choice> getDefenderChoices(cardarea *cards);

         int conflictTotal(playerstate &pState);

         void sendCharactersHome(std::list<inplaycharacter> charlist, cardarea *cards);

         int countFavorGlory(cardarea *cards);

         std::list<choice> getCharactersWithNoFate(cardarea *cards);

         void discardCharacter(cardarea *cards, int cardIndex);

         void removeFateFromCharacters(cardarea *cards);

         void discardProvinceCard(cardarea *cards, int cardIndex);
         
         void readyAllCharacters(cardarea *cards);

         std::list<choice> getProvinceDynastyChoices(cardarea *cards, dynastyCardStatus dcs);
      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
   };
}

#endif //_DYNASTY_CARD_MANAGER_H_
