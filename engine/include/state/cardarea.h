#ifndef _CARD_AREA_H_
#define _CARD_AREA_H_

#include "state/character.h"
#include "card.h"
#include <list>
#include <vector>

namespace l5r
{
   class cardarea
   {
      public:
         cardarea();
         ~cardarea();

         //bool operator==(const cardarea &ca);

         // all these integers are referencing cardIds (below)
         /*
         std::list<int> dynastyDeck;
         std::list<int> dynastyDiscard;
         std::list<int> conflictDeck;
         std::list<int> conflictDiscard;
         std::list<int> conflictHand;
         std::list<int> pendingMulligan;
         */
         //int pendingFateCard; // card awaiting fate
         std::vector<CardSharedPtr> dynastyDeck;
         std::vector<CardSharedPtr> dynastyDiscard;
         std::vector<CardSharedPtr> conflictDeck;
         std::vector<CardSharedPtr> conflictDiscard;
         std::vector<CardSharedPtr> conflictHand;
         std::vector<CardSharedPtr> pendingMulligan;
         CardSharedPtr pendingFateCard; // card awaiting fate

         //std::list<provinceStack> provinceArea;
         std::vector<CardSharedPtr> provinceArea;

         // for now this is 1 to 1 with provinceArea
         std::vector<CardSharedPtr> dynastyArea;

         //int strongholdProvince;
         CardSharedPtr strongholdProvince;
         CardSharedPtr stronghold;
         std::vector<CardSharedPtr> atHome;
   };
};

#endif // _CARD_AREA_H_

