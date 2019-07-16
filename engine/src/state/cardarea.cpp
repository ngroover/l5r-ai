#include "state/cardarea.h"
#include <set>

using namespace l5r;


cardarea::cardarea()
{
}

cardarea::~cardarea()
{
}

/*
bool cardarea::operator==(const cardarea &ca)
{
   std::set<int> handSet(conflictHand.begin(), conflictHand.end());
   std::set<int> caHandSet(ca.conflictHand.begin(), ca.conflictHand.end());
   std::set<int> pendingMul(pendingMulligan.begin(), pendingMulligan.end());
   std::set<int> caPendingMul(ca.pendingMulligan.begin(), ca.pendingMulligan.end());
   std::set<inplaycharacter> atHomeSet(atHome.begin(), atHome.end());
   std::set<inplaycharacter> caAtHomeSet(ca.atHome.begin(), ca.atHome.end());

   return(dynastyDeck == ca.dynastyDeck &&
      dynastyDiscard == ca.dynastyDiscard &&
      conflictDeck == ca.conflictDeck &&
      conflictDiscard == ca.conflictDiscard &&
      handSet == caHandSet &&
      pendingMul == caPendingMul &&
      pendingFateCard == ca.pendingFateCard &&
      provinceArea == ca.provinceArea &&
      strongholdProvince == ca.strongholdProvince &&
      stronghold == ca.stronghold &&
      atHomeSet == caAtHomeSet);
}
*/
