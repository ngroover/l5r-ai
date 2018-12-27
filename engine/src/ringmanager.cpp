#include "ringmanager.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace l5r;

ringManager::ringManager(std::shared_ptr<gamestate> state): state(state)
{
}

ringManager::~ringManager()
{
}

void ringManager::setAllUnclaimed()
{
   state->unclaimed_rings.clear();
   state->unclaimed_rings.push_back(ring::air);
   state->unclaimed_rings.push_back(ring::fire);
   state->unclaimed_rings.push_back(ring::earth);
   state->unclaimed_rings.push_back(ring::water);
   state->unclaimed_rings.push_back(ring::_void);
}

std::list<choice> ringManager::getConflictChoices(playerstate &pState)
{
   std::list<choice> list;
   std::vector<conflicttype> available;
   for(auto ac: pState.availableConflicts)
   {
      if(std::find(available.begin(), available.end(), ac) == available.end())
      {
         choice c(getConflictTypeName(ac), choicetype::conflict_type);
         c.setConflictType(ac);
         list.push_back(c);
         available.push_back(ac);
      }
   }
   return list;
}

void ringManager::initializeConflicts(playerstate &pState)
{
   pState.numConflicts = 2;
   pState.availableConflicts.clear();
   pState.availableConflicts.push_back(conflicttype::military);
   pState.availableConflicts.push_back(conflicttype::political);
}

void ringManager::chooseConflictType(conflicttype type)
{
   state->conflict_type = type;
}

std::string ringManager::getConflictTypeName(conflicttype type)
{
   switch(type)
   {
      case conflicttype::military:
         return "Military";
      case conflicttype::political:
         return "Political";
   }
   return "";
}

std::list<choice> ringManager::getConflictRingChoices()
{
   std::list<choice> list;
   for(auto r: state->unclaimed_rings)
   {
      choice c(getRingName(r), choicetype::ring);
      c.setChosenRing(r);
      list.push_back(c);
   }
   return list;
}

std::string ringManager::getRingName(ring r)
{
   switch(r)
   {
      case ring::air:
         return "Air";
      case ring::earth:
         return "Earth";
      case ring::water:
         return "Water";
      case ring::fire:
         return "Fire";
      case ring::_void:
         return "Void";
   }
   return "";
}

void ringManager::chooseConflictRing(ring r)
{
   state->contested_ring = r;
   for(auto uc=state->unclaimed_rings.begin();uc!=state->unclaimed_rings.end();uc++)
   {
      if(*uc == r)
      {
         state->unclaimed_rings.erase(uc);
         uc=state->unclaimed_rings.end();
      }
   }
}

void ringManager::printCurrentConflict(std::string playerName)
{
   std::cout << playerName << " is attacking " << 
         getConflictTypeName(state->conflict_type) << " " <<
         getRingName(state->contested_ring) << std::endl;
}
