#include "decklistmanager.h"
#include <gtest/gtest.h>

using namespace l5r;

TEST(DecklistManager, findLionDeck) {
   std::unique_ptr<DecklistManager> dm = std::make_unique<DecklistManager>("./decks/data");

   auto liondeck = dm->findDeck("Lion Suggested Deck");

   std::vector<std::string> expectedCards = {
         "yojin-no-shiro",
         "keeper-of-water",
         "manicured-garden",
         "ancestral-lands",
         "night-raid",
         "the-art-of-war",
         "shameful-display",
         "obstinate-recruit",
         "ikoma-prodigy",
         "matsu-berserker",
         "steadfast-samurai",
         "akodo-gunso",
         "deathseeker",
         "venerable-historian",
         "kitsu-spiritcaller",
         "lion-s-pride-brawler",
         "matsu-beiona",
         "honored-general",
         "ikoma-eiji",
         "akodo-toturi",
         "staging-ground",
         "otomo-courtier",
         "otomo-courtier",
         "otomo-courtier",
         "seppun-guardsman",
         "seppun-guardsman",
         "seppun-guardsman",
         "keeper-initiate",
         "keeper-initiate",
         "miya-mystic",
         "miya-mystic",
         "miya-mystic",
         "wandering-ronin",
         "wandering-ronin",
         "wandering-ronin",
         "favorable-ground",
         "imperial-storehouse",
         "vengeful-oathkeeper",
         "master-of-the-spear",
         "guidance-of-the-ancestors",
         "honored-blade",
         "sashimono",
         "ready-for-battle",
         "stand-your-ground",
         "way-of-the-lion",
         "for-greater-glory",
         "strength-in-numbers",
         "iuchi-wayfinder",
         "ide-messenger",
         "favored-mount",
         "spyglass",
         "breakthrough",
         "captive-audience",
         "fine-katana",
         "fine-katana",
         "ornate-fan",
         "ornate-fan",
         "banzai",
         "banzai",
         "court-games",
         "court-games",
         "charge",
         "charge",
         "fallen-in-battle",
         "fallen-in-battle",
         "rout",
         "rout"
   };

   ASSERT_EQ(liondeck->getList(), expectedCards);
}

