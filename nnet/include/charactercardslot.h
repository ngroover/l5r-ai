#ifndef _CHARACTER_CARD_SLOT_H_
#define _CHARACTER_CARD_SLOT_H_

namespace l5r
{
   enum class CharacterSlotStatus
   {
      in_deck=0,
      province1,
      province2,
      province3,
      province4,
      at_home,
      in_conflict,
      in_mulligan,
      // in conflict deck (conflict characters)
      // in hand(conflict characters)
      // NOTE: keep size constant up to date below
   };

   const int numCharacterStatus = 8;
   const int maxFateOnCharacter = 11;

   class CharacterCardSlot
   {
      public:
         CharacterCardSlot();
         ~CharacterCardSlot();

         void setState(CharacterSlotStatus state);

         void setFate(int numFate);

         void setBowed(bool bowed);

         void setRevealed(bool revealed);

         // writes out neural network double values
         void setOutput(double *input);

         // TODO: Dynamically get size
         // 8 different states
         // +
         // 11 fate slots (makes a round 20 size, this is 0 to 10 fate)
         // +
         // 1 bowed or ready slot
         // +
         // 1 revealed slot
         // = 21
         const int getSize(){ return numCharacterStatus + maxFateOnCharacter + 1 + 1; };
         
      private:
         CharacterSlotStatus state;

         int fate;
         bool bowed;
         bool revealed;
   };
}
#endif // _CHARACTER_CARD_SLOT_H_
