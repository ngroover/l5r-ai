#include "conflictresolutionmanager.h"
#include "gamestateintfc.h"
#include "state/cardarea.h"
#include "state/conflict.h"
#include "turnmanager.h"
#include "tokenmanager.h"
#include "carddatamanager.h"
#include "ringmanager.h"
#include <iostream>

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

   if(attackerStr > 0 && attackerStr >= defenderStr)
   {
      cr.winner = conflictwinner::attacker;
      int provinceStr = cardMgr->getProvinceStr(global->contested_province);
      if((attackerStr - defenderStr) >= provinceStr)
      {
         cr.brokeProvince = true;
         breakProvince(stateIntfc->getPlayerCards(), global->contested_province);
         if(defender->strongholdProvince == global->contested_province)
         {
            std::cout << stateIntfc->getOpponentName() << " won the game!" << std::endl;
            turnMgr.declareLoser();
            state->currentPhase = phase::gameover;
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
         if(tokens.getHonor() <= 0)
         {
            std::cout << stateIntfc->getPlayerName() << " loses due to honor loss" << std::endl;
            turnMgr.declareLoser();
            state->currentPhase = phase::gameover;
         }
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
