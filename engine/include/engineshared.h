#ifndef _ENGINE_SHARED_H_
#define _ENGINE_SHARED_H_

#include <gamestate.h>
#include <map>
#include <memory>
#include "agent.h"
#include "cards.h"
#include "card.h"

namespace l5r
{
   class engineShared
   {
      public:
         engineShared();
         ~engineShared();

         // public data
         gamestate state;
         std::unique_ptr<agent> player1,player2;
         std::map<cards,card> cardList;

         // public functions
         std::unique_ptr<agent> &getCurrentPlayer();
         std::unique_ptr<agent> &getOpponentPlayer();
         
         // with respect to currentAction
         playercards &getCurrentPlayerCards();
         playercards &getOpponentCards();

         void swapCurrentActionPlayer();

         // get index of a province card
         int getProvinceIndex(cards province, playercards &gameCards);
   };
}

#endif //_ENGINE_SHARED_H_
