#include "conflictmanager.h"
#include <iostream>
#include <algorithm>

using namespace l5r;


conflictManager::conflictManager( conflictState *globalState,
      std::shared_ptr<cardDataManager> cardMgr): cardMgr(cardMgr)
{
   global = globalState;
}

conflictManager::~conflictManager()
{
}

std::string conflictManager::getContestedProvinceName()
{
   return cardMgr->getCardName(global->contested_province);
}

void conflictManager::setGlobalState(conflictState *globalState)
{
   global = globalState;
}

void conflictManager::setAttacker(conflictPlayerState *attacker, std::string attackerName)
{
   this->attacker = attacker;
   this->attackerName = attackerName;
}

void conflictManager::setDefender(conflictPlayerState *defender, std::string defenderName)
{
   this->defender = defender;
   this->defenderName = defenderName;
}

void conflictManager::addAttackingCharacter(int cardIndex)
{
   attacker->inConflict.push_back(cardIndex);
}

void conflictManager::addDefendingCharacter(int cardIndex)
{
   defender->inConflict.push_back(cardIndex);
}
void conflictManager::chooseContestedProvince(int cardIndex)
{
   global->contested_province = cardIndex;
}

void conflictManager::chooseContestedRing(ring r)
{
   global->contested_ring = r;
}

void conflictManager::chooseConflictType(conflicttype ct)
{
   global->conflict_type = ct;
}

std::list<std::string> conflictManager::getAttackerNames()
{
   std::list<std::string> list;
   for(auto ch=attacker->inConflict.begin();ch!=attacker->inConflict.end();ch++)
   {
      list.push_back(cardMgr->getCardName(*ch));
   }
   return list;
}

std::list<std::string> conflictManager::getDefenderNames()
{
   std::list<std::string> list;
   for(auto ch=defender->inConflict.begin();ch!=defender->inConflict.end();ch++)
   {
      list.push_back(cardMgr->getCardName(*ch));
   }
   return list;
}

void conflictManager::passConflict()
{
   attacker->numConflicts--;
}

void conflictManager::unclaimAllRings()
{
   global->unclaimed_rings.clear();
   global->unclaimed_rings.push_back(ring::air);
   global->unclaimed_rings.push_back(ring::fire);
   global->unclaimed_rings.push_back(ring::earth);
   global->unclaimed_rings.push_back(ring::water);
   global->unclaimed_rings.push_back(ring::_void);
   attacker->availableConflicts.clear();
   defender->availableConflicts.clear();
}

std::list<choice> conflictManager::getConflictChoices()
{
   std::list<choice> list;
   std::vector<conflicttype> available;
   for(auto ac: attacker->availableConflicts)
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

void conflictManager::initializeConflicts()
{
   attacker->numConflicts = 2;
   attacker->availableConflicts.clear();
   attacker->availableConflicts.push_back(conflicttype::military);
   attacker->availableConflicts.push_back(conflicttype::political);
   defender->numConflicts = 2;
   defender->availableConflicts.clear();
   defender->availableConflicts.push_back(conflicttype::military);
   defender->availableConflicts.push_back(conflicttype::political);
}

std::string conflictManager::getConflictTypeName(conflicttype type)
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

std::list<choice> conflictManager::getConflictRingChoices()
{
   std::list<choice> list;
   for(auto r: global->unclaimed_rings)
   {
      choice c(getRingName(r), choicetype::ring);
      c.setChosenRing(r);
      list.push_back(c);
   }
   return list;
}

std::string conflictManager::getRingName(ring r)
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

void conflictManager::chooseConflictRing(ring r)
{
   global->contested_ring = r;
   for(auto uc=global->unclaimed_rings.begin();uc!=global->unclaimed_rings.end();uc++)
   {
      if(*uc == r)
      {
         global->unclaimed_rings.erase(uc);
         uc=global->unclaimed_rings.end();
      }
   }
}

std::string conflictManager::getConflictRingName()
{
   return getRingName(global->contested_ring);
}

std::string conflictManager::getCurrentConflictTypeName()
{
   return getConflictTypeName(global->conflict_type);
}

bool conflictManager::attackerWonConflict()
{
   int attackerStr=0;
   for(auto a:attacker->inConflict)
   {
      if(global->conflict_type == conflicttype::military)
      {
         attackerStr += cardMgr->getMilitaryStr(a);
      }
      else
      {
         attackerStr += cardMgr->getPoliticalStr(a);
      }
   }

   int defenderStr=0;
   for(auto d:defender->inConflict)
   {
      if(global->conflict_type == conflicttype::military)
      {
         defenderStr += cardMgr->getMilitaryStr(d);
      }
      else
      {
         defenderStr += cardMgr->getPoliticalStr(d);
      }
   }
   std::cout << "Attacker str = " << attackerStr <<
      " Defender str = " << defenderStr << std::endl;
   return attackerStr >= defenderStr;
}

bool conflictManager::defenderWonConflict()
{
}
