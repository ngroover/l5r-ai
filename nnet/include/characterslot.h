#ifndef _CHARACTER_SLOT_H_
#define _CHARACTER_SLOT_H_

namespace l5r
{
   struct CharacterSlot
   {
      double in_deck;
      double province1;
      double province2;
      double province3;
      double province4;
      double at_home;
      double in_conflict;
      double in_mulligan;
      double storedFate[11];  // supports up to 10 fate (including 0)
      double bowed;
      double revealed;  // if on a province
      //TODO: add pending fate state
   } typedef CharacterSlot;
}
#endif // _CHARACTER_SLOT_H_
