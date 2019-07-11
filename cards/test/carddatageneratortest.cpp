#include "carddatageneratortest.h"
#include "carddata.h"

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( CardDataGeneratorTest );

void CardDataGeneratorTest::setUp()
{
   generator = std::make_unique<CardDataGenerator>("./cards/data/");
}

void CardDataGeneratorTest::tearDown()
{
   // nothing to do
}

void CardDataGeneratorTest::characterTest()
{
   // check a lion character
   auto lpb = generator->generateCard("lion-s-pride-brawler");
   CPPUNIT_ASSERT_EQUAL(lpb->fateCost, 3);
   CPPUNIT_ASSERT_EQUAL(lpb->name, std::string("Lion's Pride Brawler"));
   CPPUNIT_ASSERT_EQUAL(lpb->id, std::string("lion-s-pride-brawler"));
   CPPUNIT_ASSERT(lpb->side ==  deckside::dynasty);
   CPPUNIT_ASSERT_EQUAL(lpb->militarySkill, 3);
   CPPUNIT_ASSERT_EQUAL(lpb->politicalSkill, 2);
   CPPUNIT_ASSERT_EQUAL(lpb->glory, 1);
   CPPUNIT_ASSERT(!lpb->militaryDash);
   CPPUNIT_ASSERT(!lpb->politicalDash);
   CPPUNIT_ASSERT(lpb->type == cardtype::character);
   CPPUNIT_ASSERT(lpb->clan == clantype::lion);

   // check a crane characters
   auto dc = generator->generateCard("doji-challenger");
   CPPUNIT_ASSERT_EQUAL(dc->fateCost, 3);
   CPPUNIT_ASSERT_EQUAL(dc->name, std::string("Doji Challenger"));
   CPPUNIT_ASSERT_EQUAL(dc->id, std::string("doji-challenger"));
   CPPUNIT_ASSERT(dc->side ==  deckside::dynasty);
   CPPUNIT_ASSERT_EQUAL(dc->militarySkill, 3);
   CPPUNIT_ASSERT_EQUAL(dc->politicalSkill, 3);
   CPPUNIT_ASSERT_EQUAL(dc->glory, 2);
   CPPUNIT_ASSERT(!dc->militaryDash);
   CPPUNIT_ASSERT(!dc->politicalDash);
   CPPUNIT_ASSERT(dc->type ==  cardtype::character);
   CPPUNIT_ASSERT(dc->clan == clantype::crane);

   auto steward = generator->generateCard("steward-of-law");
   CPPUNIT_ASSERT_EQUAL(steward->influenceCost, 1);
}

void CardDataGeneratorTest::holdingTest()
{
   // check a holding
   auto storehouse = generator->generateCard("imperial-storehouse");
   CPPUNIT_ASSERT_EQUAL(storehouse->name, std::string("Imperial Storehouse"));
   CPPUNIT_ASSERT_EQUAL(storehouse->id, std::string("imperial-storehouse"));
   CPPUNIT_ASSERT(storehouse->side ==  deckside::dynasty);
   CPPUNIT_ASSERT(storehouse->type == cardtype::holding);
}

void CardDataGeneratorTest::strongholdTest()
{
   auto yojin = generator->generateCard("yojin-no-shiro");
   CPPUNIT_ASSERT(yojin->side == deckside::province);
   CPPUNIT_ASSERT_EQUAL(yojin->influencePool, 10);
}

void CardDataGeneratorTest::provinceTest()
{
   auto manicured = generator->generateCard("manicured-garden");
   CPPUNIT_ASSERT(manicured->side == deckside::province);
}
