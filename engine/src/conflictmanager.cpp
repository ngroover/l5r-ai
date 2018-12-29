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

void conflictManager::addAttackingCharacter(inplaycharacter character)
{
   attacker->inConflict.push_back(character);
}

void conflictManager::addDefendingCharacter(inplaycharacter character)
{
   defender->inConflict.push_back(character);
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
      list.push_back(cardMgr->getCardName(ch->characterCard));
   }
   return list;
}

std::list<std::string> conflictManager::getDefenderNames()
{
   std::list<std::string> list;
   for(auto ch=defender->inConflict.begin();ch!=defender->inConflict.end();ch++)
   {
      list.push_back(cardMgr->getCardName(ch->characterCard));
   }
   return list;
}

void conflictManager::passConflict()
{
   attacker->numConflicts--;
}

void conflictManager::completeConflict()
{
   attacker->numConflicts--;
}

bool conflictManager::attackerHasConflictsLeft()
{
   return attacker->numConflicts > 0;
}

bool conflictManager::defenderHasConflictsLeft()
{
   return defender->numConflicts > 0;
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
   int attackerStr=calculateStr(attacker);
   int defenderStr=calculateStr(defender);
   return (attackerStr > 0 && attackerStr >= defenderStr);
}

bool conflictManager::defenderWonConflict()
{
   int attackerStr=calculateStr(attacker);
   int defenderStr=calculateStr(defender);
   return (defenderStr > 0 && defenderStr > attackerStr);
}

bool conflictManager::provinceBroke()
{
   int attackerStr=calculateStr(attacker);
   int defenderStr=calculateStr(defender);
   int provinceStr = cardMgr->getProvinceStr(global->contested_province);
   return (attackerStr - defenderStr) >= provinceStr;
}

int conflictManager::calculateStr(conflictPlayerState *player)
{
   int strength=0;
   for(auto a:player->inConflict)
   {
      if(global->conflict_type == conflicttype::military)
      {
         strength += cardMgr->getMilitaryStr(a.characterCard);
      }
      else
      {
         strength += cardMgr->getPoliticalStr(a.characterCard);
      }
   }
   return strength;
}

void conflictManager::printConflictResult()
{
   int attackerStr=calculateStr(attacker);
   int defenderStr=calculateStr(defender);
   std::cout << "Conflict resolves" << std::endl;
   std::cout << attackerName << ":" << attackerStr << std::endl;
   std::cout << defenderName << ":" << defenderStr << std::endl;
   if(attackerStr >= defenderStr)
   {
      std::cout << attackerName << " won the conflict!" << std::endl;
   }
   else if(defenderStr > 0)
   {
      std::cout << defenderName << " won the conflict!" << std::endl;
   }
   else
   {
      std::cout << "Conflict has no winner" << std::endl;
   }
}

int conflictManager::getContestedProvince()
{
   return global->contested_province;
}

void conflictManager::attackerClaimRing()
{
   attacker->claimed_rings.push_back(global->contested_ring);
   std::cout << attackerName << " claimed the " <<
      getRingName(global->contested_ring) << " ring" << std::endl;
}

void conflictManager::defenderClaimRing()
{
   defender->claimed_rings.push_back(global->contested_ring);
   std::cout << defenderName << " claimed the " <<
      getRingName(global->contested_ring) << " ring" << std::endl;
}

void conflictManager::contestedRingUnclaimed()
{
   global->unclaimed_rings.push_back(global->contested_ring);
   std::cout << getRingName(global->contested_ring) <<  " ring remained unclaimed" << std::endl;
}

void conflictManager::bowAttackers()
{
   std::cout << "Bowing characters" << std::endl;
   for(auto &a:attacker->inConflict)
   {
      a.bowed = true;
   }
}

void conflictManager::bowDefenders()
{
   std::cout << "Bowing characters" << std::endl;
   for(auto &a:defender->inConflict)
   {
      a.bowed = true;
   }
}

std::list<inplaycharacter> conflictManager::removeAllAttackingCharacters()
{
   std::list<inplaycharacter> charlist=attacker->inConflict;
   for(auto c: charlist)
   {
      std::cout << " " << cardMgr->getCardName(c.characterCard) << std::endl;
   }
   attacker->inConflict.clear();
   return charlist;
}

std::list<inplaycharacter> conflictManager::removeAllDefendingCharacters()
{
   std::list<inplaycharacter> charlist=defender->inConflict;
   for(auto c: charlist)
   {
      std::cout << " " << cardMgr->getCardName(c.characterCard) << std::endl;
   }
   defender->inConflict.clear();
   return charlist;
}
