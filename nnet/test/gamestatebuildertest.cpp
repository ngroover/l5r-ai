#include "gamestatebuildertest.h"
#include "gamestatebuilder.h"
#include <cstring>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( GamestateBuilderTest );

void GamestateBuilderTest::setUp()
{
   builder = new GamestateBuilder(3, 4, 5);
}

void GamestateBuilderTest::tearDown()
{
   delete builder;
}

void GamestateBuilderTest::checkCharacters()
{
   double *rawData = builder->getRawData();
   memset(rawData, 0, sizeof(double)*builder->getTotalSize());

   CharacterSlot *cs = builder->getCharacter(0);
   cs->in_deck = 1.0;
   cs->province1 = 2.0;
   cs->province2 = 3.0;
   cs->province3 = 4.0;

   CPPUNIT_ASSERT(rawData[0] == 1.0 &&
      rawData[1] == 2.0 && rawData[2] == 3.0 &&
      rawData[3] == 4.0);

   cs = builder->getCharacter(2);
   cs->in_deck = 5.0;
   cs->province1 = 6.0;
   cs->province2 = 7.0;
   cs->province3 = 8.0;

   // look at CharacterSlot size and do math manually to figure out offset
   const int baseOffset=22*2;
   CPPUNIT_ASSERT(rawData[baseOffset] == 5.0 &&
      rawData[baseOffset+1] == 6.0 && rawData[baseOffset+2] == 7.0 &&
      rawData[baseOffset+3] == 8.0);
}

void GamestateBuilderTest::checkHoldings()
{
   double *rawData = builder->getRawData();
   memset(rawData, 0, sizeof(double)*builder->getTotalSize());

   HoldingSlot *hs = builder->getHolding(0);
   hs->in_deck = 1.0;
   hs->province1 = 2.0;
   hs->province2 = 3.0;
   hs->province3 = 4.0;
   hs->province4 = 5.0;

   const int baseOffset=22*3;
   CPPUNIT_ASSERT(rawData[baseOffset] == 1.0 &&
      rawData[baseOffset+1] == 2.0 && rawData[baseOffset+2] == 3.0 &&
      rawData[baseOffset+3] == 4.0 && rawData[baseOffset+4] == 5.0);

   hs = builder->getHolding(3);
   hs->in_deck = 5.0;
   hs->province1 = 6.0;
   hs->province2 = 7.0;
   hs->province3 = 8.0;
   hs->province4 = 9.0;

   const int baseOffset2=22*3+(6*3);
   CPPUNIT_ASSERT(rawData[baseOffset2] == 5.0 &&
      rawData[baseOffset2+1] == 6.0 && rawData[baseOffset2+2] == 7.0 &&
      rawData[baseOffset2+3] == 8.0 && rawData[baseOffset2+4] == 9.0);
}
