#ifndef _CARD_AREA_MANAGER_H_
#define _CARD_AREA_MANAGER_H_

#include <string>
#include <vector>
#include <memory>
#include "decklist.h"

namespace l5r
{
   class cardarea;
   class cardDataManager;
   class CardAreaManager
   {
      public:
         CardAreaManager(cardarea *cardArea, std::string name,
            std::shared_ptr<cardDataManager> cardMgr);
         ~CardAreaManager();

         // put the cards in their rightful stacks
         void setupCards(Decklist deck);

      private:
         cardarea *cardArea;
         std::string name;
         std::shared_ptr<cardDataManager> cardMgr;

   };
};
#endif 
