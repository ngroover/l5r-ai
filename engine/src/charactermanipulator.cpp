#include "charactermanipulator.h"
#include "gamestateintfc.h"
#include "state/conflict.h"
#include "carddatamanager.h"
#include <iostream>

using namespace l5r;

CharacterManipulator::CharacterManipulator(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr) : stateIntfc(stateIntfc), cardMgr(cardMgr)
{
}

CharacterManipulator::~CharacterManipulator()
{
}

void CharacterManipulator::bowParticipants()
{
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getDefenderConflictState();

   std::cout << "Bowing characters" << std::endl;
   for(auto &a:attacker->inConflict)
   {
      a->bowed = true;
   }

   for(auto &a:defender->inConflict)
   {
      a->bowed = true;
   }
}

void CharacterManipulator::movePartipantsHome()
{
   auto attacker = stateIntfc->getAttackerCards();
   auto defender = stateIntfc->getDefenderCards();
   auto attackerState = stateIntfc->getAttackerConflictState();
   auto defenderState = stateIntfc->getDefenderConflictState();

   for(auto c: attackerState->inConflict)
   {
      std::cout << " " << c->data->name << std::endl;
      attacker->atHome.push_back(c);
   }
   attackerState->inConflict.clear();

   for(auto c: defenderState->inConflict)
   {
      std::cout << " " << c->data->name << std::endl;
      defender->atHome.push_back(c);
   }
   defenderState->inConflict.clear();
}

void CharacterManipulator::moveCharacterToConflict(conflictPlayerState *cps, cardarea *ca, CardSharedPtr cardChoice)
{
   for(auto ch=ca->atHome.begin();ch!=ca->atHome.end();ch++)
   {
      if((*ch) == cardChoice)
      {
         ca->atHome.erase(ch);
         cps->inConflict.push_back(*ch);
         ch = ca->atHome.end();
      }
   }
}
