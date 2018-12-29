#ifndef _CARD_DATA_MANAGER_H_
#define _CARD_DATA_MANAGER_H_

#include <memory>
#include "cardgenerator.h"
#include "card.h"
#include "gamestate.h"

namespace l5r
{
   class cardDataManager
   {
      public:
         cardDataManager(std::shared_ptr<gamestate> state);
         ~cardDataManager();

         void loadDecklist(decklist dl, int playerNum);

         // shortcut functions
         cardtype getCardType(cards c);

         std::string getCardName(int index);
         int getStrongholdHonor(int index);
         int getFateCost(int index);
         int getProvinceStr(int index);

         int getMilitaryStr(int index);
         int getPoliticalStr(int index);
         int getGlory(int index);

      private:
         std::map<cards,card> cardMap;
         std::shared_ptr<gamestate> state;

         cardgenerator cg;
   };
};

#endif // _CARD_DATA_MANAGER_H_
