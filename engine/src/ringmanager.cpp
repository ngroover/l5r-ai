#include "ringmanager.h"
#include "gamestateintfc.h"
#include "state/conflict.h"
#include <iostream>

using namespace l5r;

RingManager::RingManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr) : stateIntfc(stateIntfc), cardMgr(cardMgr)
{
}

RingManager::~RingManager()
{
}

void RingManager::initialize()
{
   auto global = stateIntfc->getGlobalConflictState();
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getAttackerConflictState();

   global->unclaimed_rings.clear();
   unclaimedring ur;
   ur.fate = 0;
   ur.type = ring::air;
   global->unclaimed_rings.push_back(ur);
   ur.type = ring::fire;
   global->unclaimed_rings.push_back(ur);
   ur.type = ring::earth;
   global->unclaimed_rings.push_back(ur);
   ur.type = ring::water;
   global->unclaimed_rings.push_back(ur);
   ur.type = ring::_void;
   global->unclaimed_rings.push_back(ur);
   attacker->availableConflicts.clear();
   defender->availableConflicts.clear();
}

void RingManager::initializeConflicts()
{
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getAttackerConflictState();

   attacker->numConflicts = 2;
   attacker->availableConflicts.clear();
   attacker->availableConflicts.push_back(conflicttype::military);
   attacker->availableConflicts.push_back(conflicttype::political);
   defender->numConflicts = 2;
   defender->availableConflicts.clear();
   defender->availableConflicts.push_back(conflicttype::military);
   defender->availableConflicts.push_back(conflicttype::political);
}

void RingManager::unclaimRings()
{
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getAttackerConflictState();
   auto global = stateIntfc->getGlobalConflictState();

   auto r = attacker->claimed_rings.begin();
   while(r!=attacker->claimed_rings.end())
   {
      unclaimedring ur;
      ur.type = *r;
      ur.fate = 0;
      global->unclaimed_rings.push_back(ur);
      std::cout << "Returning " << getRingName(*r) << " ring" << std::endl;
      r = attacker->claimed_rings.erase(r);
   }
   r= defender->claimed_rings.begin();
   while(r!=defender->claimed_rings.end())
   {
      unclaimedring ur;
      ur.type = *r;
      ur.fate = 0;
      global->unclaimed_rings.push_back(ur);
      std::cout << "Returning " << getRingName(*r) << " ring" << std::endl;
      r = defender->claimed_rings.erase(r);
   }
}

std::string l5r::getRingName(ring r)
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

void RingManager::putFateOnRings()
{
   auto global = stateIntfc->getGlobalConflictState();
   for(auto &ur:global->unclaimed_rings)
   {
      ur.fate++;
      std::cout << "Adding 1 fate to " << getRingName(ur.type) << " ring" << std::endl;
   }
}
