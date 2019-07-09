#include "decklistvalidator.h"
#include <glog/logging.h>
#include <dirent.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace l5r;

DecklistValidator::DecklistValidator(CardDataGeneratorSharedPtr cardData) : cardData(cardData)
{
}

DecklistValidator::~DecklistValidator()
{
}

bool DecklistValidator::isDeckValid(const Decklist &deck)
{
   // check for 1 and only 1 stronghold
   std::vector<std::string> strongholds;
   for (const auto &c : deck.getList() )
   {
      auto card = cardData->generateCard(c);

      if(card->type == cardtype::stronghold)
      {
         strongholds.push_back(c);
      }
   }

   if(strongholds.size() < 1)
   {
      reasonString = "No stronghold card";
      return false;
   }
   if(strongholds.size() > 1)
   {
      reasonString = "Too many stronghold cards";
      return false;
   }
}

std::string DecklistValidator::getInvalidReason()
{
   return reasonString;
}
