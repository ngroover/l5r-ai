#ifndef _CONFLICT_CARD_MANAGER_H_
#define _CONFLICT_CARD_MANAGER_H_

#include "state/gamestate.h"
#include "carddatamanager.h"
#include "choice.h"

namespace l5r
{
   class cardarea;

   class conflictCardManager
   {
      public:
         conflictCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr);
         ~conflictCardManager();


         // current player draws numCards
         void drawCards(int numCards, cardarea *cards, std::string playerName);
         int getNumCards(cardarea *cards);

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
   };
}

#endif //_CONFLICT_CARD_MANAGER_H_
