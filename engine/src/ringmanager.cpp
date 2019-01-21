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
}

void RingManager::initializeConflicts()
{
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getDefenderConflictState();

   attacker->politicalConflictsLeft = 1;
   attacker->militaryConflictsLeft = 1;
   attacker->totalConflictsLeft = 2;
   defender->politicalConflictsLeft = 1;
   defender->militaryConflictsLeft = 1;
   defender->totalConflictsLeft = 2;
}

void RingManager::unclaimRings()
{
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getDefenderConflictState();
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
