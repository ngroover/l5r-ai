#include "charactercardslot.h"
#include <iostream>

using namespace l5r;

CharacterCardSlot::CharacterCardSlot()
{
   fate = 0;
   bowed=false;
   revealed=false;
   state=CharacterSlotStatus::in_deck;
}

CharacterCardSlot::~CharacterCardSlot()
{
}

void CharacterCardSlot::setState(CharacterSlotStatus state)
{
   this->state = state;
}

void CharacterCardSlot::setFate(int numFate)
{
   this->fate = numFate;
}

void CharacterCardSlot::setBowed(bool bowed)
{
   this->bowed = bowed;
}

void CharacterCardSlot::setOutput(double *input)
{
   for(int i=0;i<getSize();i++)
   {
      input[i] = 0.0;
   }

   // set status
   int index = static_cast<std::underlying_type<CharacterSlotStatus>::type>(state);
   input[index] = 1.0;

   // set fate on character
   if(fate >= maxFateOnCharacter)
   {
      std::cout << "Fate higher than " << maxFateOnCharacter-1 << " cannot assign it" << std::endl;
      return;
   }
   input[numCharacterStatus+fate] = 1.0;
   
   // set bowed value
   input[numCharacterStatus+maxFateOnCharacter] = (bowed ? 1.0 : 0.0);

   // set revealed value
   input[numCharacterStatus+maxFateOnCharacter+1] = (revealed ? 1.0 : 0.0);
}

void CharacterCardSlot::setRevealed(bool revealed)
{
   if( state != CharacterSlotStatus::province1 && 
    state != CharacterSlotStatus::province2 && 
    state != CharacterSlotStatus::province3 && 
    state != CharacterSlotStatus::province4) 
   {
      std::cout << "Cannot be revealed if it's not on a province" << std::endl;
   }
   else
   {
      this->revealed = revealed;
   }
}
