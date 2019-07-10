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

