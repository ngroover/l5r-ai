#include "decklistvalidator.h"
#include "carddatagenerator.h"
#include <gtest/gtest.h>

using namespace l5r;

TEST(DecklistValidator, noStronghold) {
   // not a full deck just some random cards; testing no stronghold
   Decklist deck("test deck", 
      { "seeker-of-air",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout" });

   CardDataGeneratorSharedPtr cardData = std::make_shared<CardDataGenerator>("./cards/data");
   DecklistValidator validator(cardData);

   ASSERT_FALSE(validator.isDeckValid(deck));
   
   ASSERT_EQ(validator.getInvalidReason(), "No stronghold card");
}

TEST(DecklistValidator, tooManyStrongholds) {
   // not a full deck just some random cards; testing too many strongholds
   Decklist deck("test deck", 
      { "shizuka-toshi",
      "yojin-no-shiro",
      "seeker-of-air",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout" });

   CardDataGeneratorSharedPtr cardData = std::make_shared<CardDataGenerator>("./cards/data");
   DecklistValidator validator(cardData);

   ASSERT_FALSE(validator.isDeckValid(deck));
   
   ASSERT_EQ(validator.getInvalidReason(), "Too many stronghold cards");
}

TEST(DecklistValidator, tooManyRoles) {
   // not a full deck just some random cards; testing too many roles
   Decklist deck("test deck", 
      { "shizuka-toshi",
      "seeker-of-air",
      "seeker-of-water",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout" });

   CardDataGeneratorSharedPtr cardData = std::make_shared<CardDataGenerator>("./cards/data");
   DecklistValidator validator(cardData);

   ASSERT_FALSE(validator.isDeckValid(deck));
   
   ASSERT_EQ(validator.getInvalidReason(), "Too many role cards");
}

TEST(DecklistValidator, tooManyDynastyClans) {
   Decklist deck("test deck", 
      { "shizuka-toshi",
      "seeker-of-air",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout",
      "doji-gift-giver",
      "savvy-politician",
      "daidoji-nerishma",
      "doji-challenger",
      "kakita-asami",
      "kakita-kaezin",
      "asahina-storyteller",
      "guest-of-honor",
      "doji-hotaru",
      "artisan-academy",
      "otomo-courtier",
      "otomo-courtier",
      "otomo-courtier",
      "seppun-guardsman",
      "seppun-guardsman",
      "seppun-guardsman",
      "miya-mystic",
      "miya-mystic",
      "miya-mystic",
      "seeker-initiate",
      "seeker-initiate",
      "wandering-ronin",
      "wandering-ronin",
      "wandering-ronin",
      "favorable-ground",
      "imperial-storehouse",
      "asahina-artisan",
      "akodo-toturi",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout" });

   CardDataGeneratorSharedPtr cardData = std::make_shared<CardDataGenerator>("./cards/data");
   DecklistValidator validator(cardData, 30, 30);

   ASSERT_FALSE(validator.isDeckValid(deck));
   
   ASSERT_EQ(validator.getInvalidReason(), "Too many out of clan dynasty cards");
}

TEST(DecklistValidator, tooManyConflictClans) {
   // not a full deck just some random cards; testing too many dynasty clans

   Decklist deck("test deck", 
      { "shizuka-toshi",
      "seeker-of-air",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout",
      "doji-gift-giver",
      "savvy-politician",
      "daidoji-nerishma",
      "doji-challenger",
      "kakita-asami",
      "kakita-kaezin",
      "asahina-storyteller",
      "guest-of-honor",
      "doji-hotaru",
      "artisan-academy",
      "otomo-courtier",
      "otomo-courtier",
      "otomo-courtier",
      "seppun-guardsman",
      "seppun-guardsman",
      "seppun-guardsman",
      "miya-mystic",
      "miya-mystic",
      "miya-mystic",
      "seeker-initiate",
      "seeker-initiate",
      "wandering-ronin",
      "wandering-ronin",
      "wandering-ronin",
      "favorable-ground",
      "imperial-storehouse",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout",
      "steward-of-law",
      "political-rival",
      "above-question",
      "duelist-training",
      "height-of-fashion",
      "the-perfect-gift",
      "voice-of-honor",
      "way-of-the-crane",
      "admit-defeat",
      "noble-sacrifice",
      "display-of-power",
      "seeker-of-knowledge",
      "magnificent-kimono",
      "pacifism",
      "know-the-world",
      "fine-katana",
      "fine-katana",
      "ornate-fan",
      "ornate-fan",
      "banzai",
      "banzai",
      "contingency-plan",
      "contingency-plan",
      "court-games",
      "court-games",
      "for-shame",
      "for-shame",
      "good-omen",
      "outwit",
      "outwit",
      "ready-for-battle"
      });

   CardDataGeneratorSharedPtr cardData = std::make_shared<CardDataGenerator>("./cards/data");
   DecklistValidator validator(cardData, 30, 30);

   ASSERT_FALSE(validator.isDeckValid(deck));
   
   ASSERT_EQ(validator.getInvalidReason(), "Too many out of clan conflict cards");
}

TEST(DecklistValidator, tooMuchInfluence) {
   // not a full deck just some random cards; testing too many dynasty clans

   Decklist deck("test deck", 
      { "shizuka-toshi",
      "seeker-of-air",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout",
      "doji-gift-giver",
      "savvy-politician",
      "daidoji-nerishma",
      "doji-challenger",
      "kakita-asami",
      "kakita-kaezin",
      "asahina-storyteller",
      "guest-of-honor",
      "doji-hotaru",
      "artisan-academy",
      "otomo-courtier",
      "otomo-courtier",
      "otomo-courtier",
      "seppun-guardsman",
      "seppun-guardsman",
      "seppun-guardsman",
      "miya-mystic",
      "miya-mystic",
      "miya-mystic",
      "seeker-initiate",
      "seeker-initiate",
      "wandering-ronin",
      "wandering-ronin",
      "wandering-ronin",
      "favorable-ground",
      "imperial-storehouse",
      "asahina-artisan",
      "doji-whisperer",
      "brash-samurai",
      "cautious-scout",
      "steward-of-law",
      "political-rival",
      "above-question",
      "duelist-training",
      "height-of-fashion",
      "the-perfect-gift",
      "voice-of-honor",
      "way-of-the-crane",
      "admit-defeat",
      "noble-sacrifice",
      "display-of-power",
      "seeker-of-knowledge",
      "magnificent-kimono",
      "pacifism",
      "know-the-world",
      "fine-katana",
      "fine-katana",
      "ornate-fan",
      "ornate-fan",
      "banzai",
      "banzai",
      "contingency-plan",
      "contingency-plan",
      "court-games",
      "court-games",
      "for-shame",
      "for-shame",
      "good-omen",
      "outwit",
      "outwit",
      "display-of-power"
      });

   CardDataGeneratorSharedPtr cardData = std::make_shared<CardDataGenerator>("./cards/data");
   DecklistValidator validator(cardData, 30, 30);

   ASSERT_FALSE(validator.isDeckValid(deck));

   ASSERT_EQ(validator.getInvalidReason(), "Too much influence cost");
}
