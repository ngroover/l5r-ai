#include "characterslottest.h"
#include "charactercardslot.h"

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( CharacterSlotTest );

void CharacterSlotTest::setUp()
{
   charSlot = new CharacterCardSlot();
}

void CharacterSlotTest::tearDown()
{
   delete charSlot;
}

void CharacterSlotTest::checkState()
{
   double networkDoubles[charSlot->getSize()];

   // set the state (in_deck)
   charSlot->setState(CharacterSlotStatus::in_deck);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   matchState(networkDoubles, 0, 8);

   // set the state (province1)
   charSlot->setState(CharacterSlotStatus::province1);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   matchState(networkDoubles, 1, 8);

   // set the state (province2)
   charSlot->setState(CharacterSlotStatus::province2);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   matchState(networkDoubles, 2, 8);
}

void CharacterSlotTest::checkFate()
{
   double networkDoubles[charSlot->getSize()];

   charSlot->setFate(0);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   matchState(networkDoubles+8, 0, 11);

   charSlot->setFate(1);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   matchState(networkDoubles+8, 1, 11);

   charSlot->setFate(10);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   matchState(networkDoubles+8, 10, 11);
}

void CharacterSlotTest::checkBowed()
{
   double networkDoubles[charSlot->getSize()];

   charSlot->setBowed(false);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   CPPUNIT_ASSERT(networkDoubles[8+11] == 0.0);

   charSlot->setBowed(true);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   CPPUNIT_ASSERT(networkDoubles[8+11] == 1.0);
}

void CharacterSlotTest::checkRevealed()
{
   double networkDoubles[charSlot->getSize()];

   charSlot->setState(CharacterSlotStatus::province1);
   charSlot->setRevealed(false);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   CPPUNIT_ASSERT(networkDoubles[8+11+1] == 0.0);

   charSlot->setRevealed(true);

   // output doubles
   charSlot->setOutput(networkDoubles);

   // check the state
   CPPUNIT_ASSERT(networkDoubles[8+11+1] == 1.0);
}

void CharacterSlotTest::matchState(double *input, int position, int size)
{
   for(int i=0;i < size;i ++)
   {
      if(i == position)
      {
         CPPUNIT_ASSERT(input[i] == 1.0);
      }
      else
      {
         CPPUNIT_ASSERT(input[i] == 0.0);
      }
   }
}


