#include "imperialfavormanager.h"
#include "carddatamanager.h"
#include "state/cardarea.h"
#include "state/conflict.h"
#include "gamestateintfc.h"
#include <iostream>

using namespace l5r;

ImperialFavorManager::ImperialFavorManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr) : stateIntfc(stateIntfc), cardMgr(cardMgr)
{
   attacker = stateIntfc->getAttackerCards();
   defender = stateIntfc->getDefenderCards();
   attackerState = stateIntfc->getAttackerConflictState();
   defenderState = stateIntfc->getDefenderConflictState();
   global = stateIntfc->getGlobalConflictState();
}

ImperialFavorManager::~ImperialFavorManager()
{
}

int ImperialFavorManager::countFavorGlory(cardarea *cards)
{
   int gloryCount=0;
   for(auto c: cards->atHome)
   {
      if(!c->bowed)
      {
         gloryCount += c->data->glory;
      }
   }
   return gloryCount;
}

favorwinner ImperialFavorManager::calculateWinner()
{
   int attackerGlory = countFavorGlory(attacker);
   int attackerRings = attackerState->claimed_rings.size();
   int defenderGlory = countFavorGlory(defender);
   int defenderRings = defenderState->claimed_rings.size();
   
   int attackerTotal = attackerGlory + attackerRings;
   int defenderTotal = defenderGlory + defenderRings;

   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getDefenderConflictState();


   if(attackerTotal > defenderTotal)
   {
      attacker->hasImperialFavor = true;
      defender->hasImperialFavor = false;
      return favorwinner::attacker;
   }
   else if(defenderTotal > attackerTotal)
   {
      defender->hasImperialFavor = true;
      attacker->hasImperialFavor = false;
      return favorwinner::defender;
   }
   else
   {
      return favorwinner::neither;
   }
}

void ImperialFavorManager::initializeFavor()
{
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getDefenderConflictState();

   attacker->hasImperialFavor = false;
   defender->hasImperialFavor = false;
}

void ImperialFavorManager::changeFavorType(conflicttype newtype)
{
   std::cout << "Favor switched to " << getConflictTypeName(newtype) << std::endl;
   global->favorType = newtype;
}
