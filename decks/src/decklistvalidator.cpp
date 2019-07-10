#include "decklistvalidator.h"
#include <glog/logging.h>
#include <dirent.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <set>
#include <algorithm>

using namespace l5r;

DecklistValidator::DecklistValidator(CardDataGeneratorSharedPtr cardData) : cardData(cardData), dynastyMinimum(40), conflictMinimum(40)
{
}

DecklistValidator::DecklistValidator(CardDataGeneratorSharedPtr cardData, int dynastyMinimum, int conflictMinimum) : cardData(cardData), dynastyMinimum(dynastyMinimum), conflictMinimum(conflictMinimum)
{
}

DecklistValidator::~DecklistValidator()
{
}

bool DecklistValidator::isDeckValid(const Decklist &deck)
{
   int numStrongholds=0;
   int numRoles=0;
   int numDynasty=0;
   int numConflict=0;

   clantype strongholdType;
   std::set<clantype> dynastyClans;
   std::set<clantype> conflictClans;
   for (const auto &c : deck.getList() )
   {
      auto card = cardData->generateCard(c);

      if(card->type == cardtype::stronghold)
      {
         strongholdType = card->clan;
         numStrongholds++;
      }
      if(card->type == cardtype::role)
      {
         numRoles++;
      }

      if(card->side == deckside::dynasty)
      {
         dynastyClans.insert(card->clan);
         numDynasty++;
      }

      if(card->side == deckside::conflict)
      {
         conflictClans.insert(card->clan);
         numConflict++;
      }
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

   // dynasty must only be neutral and matching stronghold
   std::set<clantype> expectedClans = {strongholdType, clantype::neutral};
   std::set<clantype> result;
   std::set_difference(dynastyClans.begin(), dynastyClans.end(), expectedClans.begin(), expectedClans.end(), std::inserter(result, result.end()));
   if(result.size() > 0)
   {
      reasonString = "Too many out of clan dynasty cards";
      return false;
   }

   // must have between 40 and 45 dynasty cards
   if(numDynasty < dynastyMinimum || numDynasty > 45)
   {
      reasonString = "Invalid number of dynasty cards";
      return false;
   }

   std::set_difference(conflictClans.begin(), conflictClans.end(), expectedClans.begin(), expectedClans.end(), std::inserter(result, result.end()));
   if(result.size() > 1)
   {
      reasonString = "Too many out of clan conflict cards";
      return false;
   }

   // must have between 40 and 45 conflict cards
   if(numConflict < conflictMinimum || numConflict > 45)
   {
      reasonString = "Invalid number of conflict cards";
      return false;
   }

   return true;
}

std::string DecklistValidator::getInvalidReason()
{
   return reasonString;
}