#ifndef _CONFLICT_CARD_MANAGER_H_
#define _CONFLICT_CARD_MANAGER_H_

#include "state/gamestate.h"
#include "carddatamanager.h"
#include "agentmanager.h"
#include "choice.h"

namespace l5r
{
   class conflictCardManager
   {
      public:
         conflictCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr, std::shared_ptr<agentManager> agentMgr);
         ~conflictCardManager();

         void createDeck(decklist deck, int playerNum);

         // sets aside a mulligan conflict card
         void chooseMulliganCard(int cardChoice);

         // current player draws numCards
         void drawCards(int numCards, playerstate &pState, std::string playerName);
         int getNumCards();

         // performs the conflict mulligan
         void performMulligan();

         // get conflict mulligan choices
         std::list<choice> getConflictCardChoices();

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
         std::shared_ptr<agentManager> agentMgr;
   };
}

#endif //_CONFLICT_CARD_MANAGER_H_
