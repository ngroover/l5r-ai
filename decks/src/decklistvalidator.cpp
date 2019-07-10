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
   int numStrongholds=0;
   int numRoles=0;

   //std::vector<std::string> dynastyClans;
   for (const auto &c : deck.getList() )
   {
      auto card = cardData->generateCard(c);

      if(card->type == cardtype::stronghold)
      {
         numStrongholds++;
      }
      if(card->type == cardtype::role)
      {
         numRoles++;
      }
      /*
      if(card->side == deckside::dynasty)
      {
         
      }
      */
   }

   // check for 1 and only 1 stronghold
   if(numStrongholds < 1)
   {
      reasonString = "No stronghold card";
      return false;
   }
   else if(numStrongholds > 1)
   {
      reasonString = "Too many stronghold cards";
      return false;
   }

   // may have 0 or 1 role cards
   if(numRoles > 1)
   {
      reasonString = "Too many role cards";
      return false;
   }

   // must have between 40 and 45 dynasty cards

   return true;
}

std::string DecklistValidator::getInvalidReason()
{
   return reasonString;
}
