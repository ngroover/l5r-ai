#ifndef _CARD_AREA_H_
#define _CARD_AREA_H_

#include "state/province.h"
#include "state/character.h"
#include "card.h"
#include <list>

namespace l5r
{
   class cardarea
   {
      public:
         cardarea();
         ~cardarea();

         bool operator==(const cardarea &ca);

         // all these integers are referencing cardIds (below)
         std::list<int> dynastyDeck;
         std::list<int> dynastyDiscard;
         std::list<int> conflictDeck;
         std::list<int> conflictDiscard;
         std::list<int> conflictHand;
         std::list<int> pendingMulligan;
         int pendingFateCard; // card awaiting fate
         std::list<provinceStack> provinceArea;
         int strongholdProvince;
         //int stronghold;
         CardSharedPtr stronghold;
         std::list<inplaycharacter> atHome;
   };
};

#endif // _CARD_AREA_H_

