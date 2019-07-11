#include "carddatagenerator.h"
#include "carddata.h"
#include <gtest/gtest.h>

using namespace l5r;


TEST(CardDataGenerator, characterTest) {
   auto generator = std::make_unique<CardDataGenerator>("./cards/data/");

   // check a lion character
   auto lpb = generator->generateCard("lion-s-pride-brawler");
   ASSERT_EQ(lpb->fateCost, 3);
   ASSERT_EQ(lpb->name, std::string("Lion's Pride Brawler"));
   ASSERT_EQ(lpb->id, std::string("lion-s-pride-brawler"));
   ASSERT_EQ(lpb->side,  deckside::dynasty);
   ASSERT_EQ(lpb->militarySkill, 3);
   ASSERT_EQ(lpb->politicalSkill, 2);
   ASSERT_EQ(lpb->glory, 1);

   ASSERT_TRUE(!lpb->militaryDash);
   ASSERT_TRUE(!lpb->politicalDash);
   ASSERT_EQ(lpb->type, cardtype::character);
   ASSERT_EQ(lpb->clan, clantype::lion);

   // check a crane characters
   auto dc = generator->generateCard("doji-challenger");
   ASSERT_EQ(dc->fateCost, 3);
   ASSERT_EQ(dc->name, std::string("Doji Challenger"));
   ASSERT_EQ(dc->id, std::string("doji-challenger"));
   ASSERT_EQ(dc->side, deckside::dynasty);
   ASSERT_EQ(dc->militarySkill, 3);
   ASSERT_EQ(dc->politicalSkill, 3);
   ASSERT_EQ(dc->glory, 2);
   ASSERT_TRUE(!dc->militaryDash);
   ASSERT_TRUE(!dc->politicalDash);
   ASSERT_EQ(dc->type, cardtype::character);
   ASSERT_EQ(dc->clan, clantype::crane);

   auto steward = generator->generateCard("steward-of-law");
   ASSERT_EQ(steward->influenceCost, 1);
}

TEST(CardDataGenerator, holdingTest) {
   auto generator = std::make_unique<CardDataGenerator>("./cards/data/");

   // check a holding
   auto storehouse = generator->generateCard("imperial-storehouse");
   ASSERT_EQ(storehouse->name, std::string("Imperial Storehouse"));
   ASSERT_EQ(storehouse->id, std::string("imperial-storehouse"));
   ASSERT_EQ(storehouse->side, deckside::dynasty);
   ASSERT_EQ(storehouse->type, cardtype::holding);
}

TEST(CardDataGenerator, strongholdTest) {
   auto generator = std::make_unique<CardDataGenerator>("./cards/data/");
   auto yojin = generator->generateCard("yojin-no-shiro");
   ASSERT_EQ(yojin->side, deckside::province);
   ASSERT_EQ(yojin->influencePool, 10);
}

TEST(CardDataGenerator, provinceTest) {
   auto generator = std::make_unique<CardDataGenerator>("./cards/data/");
   auto manicured = generator->generateCard("manicured-garden");
   ASSERT_EQ(manicured->side, deckside::province);
   ASSERT_EQ(manicured->provinceElement, element::air);
}
