#include "conflictresolutionmanager.h"
#include "gamestateintfc.h"
#include "state/cardarea.h"
#include "state/conflict.h"
#include "turnmanager.h"
#include "tokenmanager.h"
#include "carddatamanager.h"
#include "ringmanager.h"
#include <iostream>
#include "endgame.h"

using namespace l5r;

ConflictResolutionManager::ConflictResolutionManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr) : stateIntfc(stateIntfc), cardMgr(cardMgr)
{
   attacker = stateIntfc->getAttackerCards();
   defender = stateIntfc->getDefenderCards();
   attackerState = stateIntfc->getAttackerConflictState();
   defenderState = stateIntfc->getDefenderConflictState();
   global = stateIntfc->getGlobalConflictState();
}

ConflictResolutionManager::~ConflictResolutionManager()
{
}

ConflictResult ConflictResolutionManager::resolveConflict()
{
   turnManager turnMgr(stateIntfc->getState());
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
   ConflictResult cr;
   RingManager rings(stateIntfc, cardMgr);

   int attackerStr=calculateStr(attackerState);
   int defenderStr=calculateStr(defenderState);

   auto state = stateIntfc->getState();

   std::cout << "Attacker = " << attackerStr << std::endl;
   std::cout << "Defender = " << defenderStr << std::endl;
   if(attackerStr > 0 && attackerStr >= defenderStr)
   {
      cr.winner = conflictwinner::attacker;
      int holdingBonus = findHoldingBonus();
      int provinceStr = cardMgr->getProvinceStr(global->contested_province) + holdingBonus;
      if((attackerStr - defenderStr) >= provinceStr)
      {
         cr.brokeProvince = true;
         breakProvince(stateIntfc->getPlayerCards(), global->contested_province);
         if(defender->strongholdProvince == global->contested_province)
         {
            throw EndGameException(wintype::conquest);
            //std::cout << stateIntfc->getOpponentName() << " won the game!" << std::endl;
         }
      }
      else
      {
         cr.brokeProvince = false;
      }

      if(defenderState->inConflict.size() == 0)
      {
         cr.unopposed = true;
         std::cout << "Unopposed conflict!" << std::endl;
         tokens.loseHonor(1);
      }
      else
      {
         cr.unopposed = false;
      }
      attackerState->claimed_rings.push_back(global->contested_ring);
      std::cout << stateIntfc->getAttackerName() << " claimed the " <<
         getRingName(global->contested_ring) << " ring" << std::endl;
   }
   else if(defenderStr > 0 && defenderStr > attackerStr)
   {
      defenderState->claimed_rings.push_back(global->contested_ring);
      std::cout << stateIntfc->getDefenderName() << " claimed the " <<
         getRingName(global->contested_ring) << " ring" << std::endl;
      cr.winner = conflictwinner::defender;
   }
   else
   {
      // nobody
      unclaimedring ur;
      ur.fate = 0;
      ur.type = global->contested_ring;
      global->unclaimed_rings.push_back(ur);
      std::cout << getRingName(global->contested_ring) <<  " ring remained unclaimed" << std::endl;
      cr.winner = conflictwinner::nobody;
   }

   attackerState->totalConflictsLeft--;
   if(global->conflict_type == conflicttype::military)
   {
      attackerState->militaryConflictsLeft--;
   }
   else
   {
      attackerState->politicalConflictsLeft--;
   }

   return cr;
}

int ConflictResolutionManager::calculateStr(conflictPlayerState *player)
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
   if(player->hasImperialFavor &&
      global->favorType == global->conflict_type)
   {
      strength += 1;
   }
   return strength;
}

void ConflictResolutionManager::breakProvince(cardarea *cards, int cardIndex)
{
   // nothing happens for stronghold
   // handled outside this
   for(auto &p:cards->provinceArea)
   {
      if(p.provinceCard == cardIndex)
      {
         std::cout << cardMgr->getCardName(cardIndex) << " breaks!" << std::endl;
         p.provinceStatus = provinceCardStatus::broken;
      }
   }
}

int ConflictResolutionManager::findHoldingBonus()
{
   auto defender = stateIntfc->getDefenderCards();

   for(auto prov: defender->provinceArea)
   {
      if(prov.provinceCard == global->contested_province)
      {
         if(cardMgr->getDynastyCardType(prov.dynastyCard) == dynastycardtype::holding)
         {
            return cardMgr->getHoldingBonus(prov.dynastyCard);
         }
      }
   }
   // no holding bonus
   return 0;
}
