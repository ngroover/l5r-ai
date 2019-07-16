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
      int provinceStr = global->contestedProvince->data->provinceStr + holdingBonus;
      std::cout << "Province Strength: " << provinceStr << std::endl;
      if((attackerStr - defenderStr) >= provinceStr)
      {
         cr.brokeProvince = true;
         breakProvince(stateIntfc->getPlayerCards(), global->contestedProvince);
         if(defender->strongholdProvince == global->contestedProvince)
         {
            throw EndGameException(wintype::conquest);
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
         strength += a->data->militarySkill;
      }
      else
      {
         strength += a->data->politicalSkill;
      }
   }
   if(player->hasImperialFavor &&
      global->favorType == global->conflict_type &&
      player->inConflict.size() > 0)
   {
      strength += 1;
   }
   return strength;
}

void ConflictResolutionManager::breakProvince(cardarea *cards, CardSharedPtr cardIndex)
{
   // nothing happens for stronghold
   // handled outside this
   for(auto &p:cards->provinceArea)
   {
      if(p == cardIndex)
      {
         std::cout << cardIndex->data->name << " breaks!" << std::endl;
         p->provinceStatus = provinceCardStatus::broken;
      }
   }
}

int ConflictResolutionManager::findHoldingBonus()
{
   auto defender = stateIntfc->getDefenderCards();

   auto dynastyArea = defender->dynastyArea.begin();
   for(auto prov: defender->provinceArea)
   {
      if(prov == global->contestedProvince)
      {
         if((*dynastyArea)->data->type  == cardtype::holding)
         {
            return (*dynastyArea)->data->holdingBonus;
         }
      }
      dynastyArea++;
   }
   if(global->contestedProvince == defender->strongholdProvince)
   {
      return defender->stronghold->data->holdingBonus;
   }
   // no holding bonus
   return 0;
}
