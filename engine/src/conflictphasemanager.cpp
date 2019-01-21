#include "conflictphasemanager.h"
#include "gamestateintfc.h"
#include "carddatamanager.h"
#include "charactermanipulator.h"
#include "conflictresolutionmanager.h"
#include "imperialfavormanager.h"
#include "turnmanager.h"
#include "tokenmanager.h"
#include <iostream>

using namespace l5r;

ConflictPhaseManager::ConflictPhaseManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr): stateIntfc(stateIntfc), cardMgr(cardMgr)
{
}

ConflictPhaseManager::~ConflictPhaseManager()
{
}

decision ConflictPhaseManager::getAttackersDecision()
{
   std::list<choice> list;
   auto cards = stateIntfc->getPlayerCards();
   for(auto ch=cards->atHome.begin();ch!=cards->atHome.end();ch++)
   {
      // TODO: check dashed types can't be mixed into conflict
      if(!ch->bowed)
      {
         choice c(cardMgr->getCardName(ch->characterCard), choicetype::card);
         c.setNumber(ch->characterCard);
         list.push_back(c);
      }
   }
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose an attacker", list);
   return d;
}

decision ConflictPhaseManager::getConflictTypeDecision()
{
   std::list<choice> list;
   auto attacker = stateIntfc->getAttackerConflictState();
   if(attacker->militaryConflictsLeft > 0)
   {
      choice c(getConflictTypeName(conflicttype::military), choicetype::conflict_type);
      c.setConflictType(conflicttype::military);
      list.push_back(c);
   }
   if(attacker->politicalConflictsLeft > 0)
   {
      choice c(getConflictTypeName(conflicttype::political), choicetype::conflict_type);
      c.setConflictType(conflicttype::political);
      list.push_back(c);
   }
   decision d("Choose conflict type", list);
   return d;
}

decision ConflictPhaseManager::getRingDecision()
{
   std::list<choice> list;
   auto global = stateIntfc->getGlobalConflictState();
   for(auto r: global->unclaimed_rings)
   {
      choice c(getRingName(r.type), choicetype::ring);
      c.setChosenRing(r.type);
      list.push_back(c);
   }
   decision d("Choose ring", list);
   return d;
}

decision ConflictPhaseManager::getAttackProvinceDecision()
{
   std::list<choice> list;
   int brokenCount=0;
   auto cards = stateIntfc->getOpponentCards();
   for(auto pc:cards->provinceArea)
   {
      if(pc.provinceStatus != provinceCardStatus::broken)
      {
         choice c(cardMgr->getCardName(pc.provinceCard), choicetype::card);
         c.setNumber(pc.provinceCard);
         list.push_back(c);
      }
      if(pc.provinceStatus == provinceCardStatus::broken)
      {
         brokenCount++;
      }
   }
   if(brokenCount >= 3)
   {
      choice c(cardMgr->getCardName(cards->strongholdProvince), choicetype::card);
      c.setNumber(cards->strongholdProvince);
      list.push_back(c);
   }
   decision d("Choose province", list);
   return d;
}

decision ConflictPhaseManager::getDefendersDecision()
{
   std::list<choice> list;
   auto cards = stateIntfc->getPlayerCards();
   for(auto ch=cards->atHome.begin();ch!=cards->atHome.end();ch++)
   {
      // TODO: check dashed types can't be mixed into conflict
      if(!ch->bowed)
      {
         choice c(cardMgr->getCardName(ch->characterCard), choicetype::card);
         c.setNumber(ch->characterCard);
         list.push_back(c);
      }
   }
   list.push_back(choice("Pass", choicetype::pass));
   decision d("Choose defender", list);
   return d;
}

decision ConflictPhaseManager::getFavorDecision()
{
   std::list<choice> list;
   choice m(getConflictTypeName(conflicttype::military), choicetype::conflict_type);
   m.setConflictType(conflicttype::military);
   list.push_back(m);
   choice p(getConflictTypeName(conflicttype::political), choicetype::conflict_type);
   p.setConflictType(conflicttype::political);
   list.push_back(p);
   decision d("Choose favor type", list);
   return d;
}

void ConflictPhaseManager::doChooseAttackers(choice c)
{
   CharacterManipulator manipulator(stateIntfc, cardMgr);
   auto attacker = stateIntfc->getAttackerConflictState();

   if(c.getType() == choicetype::card)
   {
      // move character in
      manipulator.moveCharacterToConflict(stateIntfc->getAttackerConflictState(), stateIntfc->getPlayerCards(), c.getNumber());
   }
   else if(c.getType() == choicetype::pass)
   {
      if(attacker->inConflict.size() > 0)
      {
         auto state = stateIntfc->getState();
         state->currentSubPhase = subphase::choose_conflicttype;
      }
      else
      {
         std::cout << "Pass conflict" << std::endl;

         attacker->totalConflictsLeft--;
         processEndConflict();
      }
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}


void ConflictPhaseManager::processEndConflict()
{
   ImperialFavorManager imperialFavor(stateIntfc, cardMgr);
   turnManager turnMgr(stateIntfc->getState());

   auto state = stateIntfc->getState();

   state->currentSubPhase = subphase::choose_attackers;
   auto attacker = stateIntfc->getAttackerConflictState();
   auto defender = stateIntfc->getDefenderConflictState();
   if(defender->totalConflictsLeft > 0)
   {
      turnMgr.giveDefenderAction();
      turnMgr.swapConflict();
   }
   else if(attacker->totalConflictsLeft > 0)
   {
      // attacker gets another conflict
      // (probably won't ever happen with current card set)
      turnMgr.giveAttackerAction();
   }
   else
   {
      switch(imperialFavor.calculateWinner())
      {
         case favorwinner::attacker:
            turnMgr.giveAttackerAction();
            state->currentSubPhase = subphase::choose_favor;
            break;
         case favorwinner::defender:
            turnMgr.giveDefenderAction();
            state->currentSubPhase = subphase::choose_favor;
            break;
         case favorwinner::neither:
            std::cout << "Imperial favor stays" << std::endl;
            state->currentPhase = phase::fate;
            state->currentSubPhase = subphase::choose_discard;
            turnMgr.setActionToCurrentTurn();
            break;

      }
   }
}

void ConflictPhaseManager::doChooseConflictType(choice c)
{
   auto state = stateIntfc->getState();
   auto global = stateIntfc->getGlobalConflictState();

   if(c.getType() == choicetype::conflict_type)
   {
      global->conflict_type = c.getConflictType();
      state->currentSubPhase = subphase::choose_ring;
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

void ConflictPhaseManager::doChooseRing(choice c)
{
   auto state = stateIntfc->getState();
   auto global = stateIntfc->getGlobalConflictState();

   if(c.getType() == choicetype::ring)
   {
      global->contested_ring = c.getChosenRing();
      for(auto uc=global->unclaimed_rings.begin();uc!=global->unclaimed_rings.end();uc++)
      {
         if(uc->type == global->contested_ring)
         {
            global->unclaimed_rings.erase(uc);
            uc=global->unclaimed_rings.end();
         }
      }
      state->currentSubPhase = subphase::choose_province;
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

void ConflictPhaseManager::doChooseProvince(choice c)
{
   auto state = stateIntfc->getState();
   auto global = stateIntfc->getGlobalConflictState();
   auto attacker = stateIntfc->getAttackerConflictState();
   turnManager turnMgr(stateIntfc->getState());

   if(c.getType() == choicetype::card)
   {
      std::string name = stateIntfc->getPlayerName();
      // TODO: move to a conflict manager
      global->contested_province = c.getNumber();
      std::cout << name << " initiated a " << getConflictTypeName(global->conflict_type)
         << " " << getRingName(global->contested_ring) << " "
         << "at " << cardMgr->getCardName(global->contested_province) << " with" << std::endl;
      printParticipating(attacker);

      state->currentSubPhase = subphase::choose_defenders;
      turnMgr.swapAction();
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

void ConflictPhaseManager::printParticipating(conflictPlayerState *cps)
{
   if(cps->inConflict.size() > 0)
   {
      for(auto ch=cps->inConflict.begin();ch!=cps->inConflict.end();ch++)
      {
         std::cout << " " << cardMgr->getCardName(ch->characterCard) << std::endl;
      }
   }
   else
   {
      std::cout << " Nobody" << std::endl;
   }
}

void ConflictPhaseManager::doChooseDefenders(choice c)
{
   tokenManager tokens(stateIntfc->getPlayerTokens(), stateIntfc->getPlayerName());
   auto defender = stateIntfc->getDefenderConflictState();
   auto state = stateIntfc->getState();
   ConflictResolutionManager conflictResolver(stateIntfc, cardMgr);
   CharacterManipulator manipulator(stateIntfc, cardMgr);

   if(c.getType() == choicetype::card)
   {
      manipulator.moveCharacterToConflict(stateIntfc->getDefenderConflictState(), stateIntfc->getPlayerCards(), c.getNumber());
   }
   else if(c.getType() == choicetype::pass)
   {
      std::string name = stateIntfc->getPlayerName();
      std::cout << name << " Defending with" << std::endl;
      printParticipating(defender);

      ConflictResult result = conflictResolver.resolveConflict();
   
      CharacterManipulator manipulator(stateIntfc, cardMgr);
      manipulator.bowParticipants();
      manipulator.movePartipantsHome();


      // process next conflict
      processEndConflict();
   }
   else
   {
      throw std::runtime_error("Invalid choice");
   }
}

void ConflictPhaseManager::doChooseFavor(choice c)
{
   ImperialFavorManager imperialFavor(stateIntfc, cardMgr);
   turnManager turnMgr(stateIntfc->getState());
   auto state = stateIntfc->getState();

   if(c.getType() == choicetype::conflict_type)
   {
      imperialFavor.changeFavorType(c.getConflictType());
      state->currentPhase = phase::fate;
      state->currentSubPhase = subphase::choose_discard;
      turnMgr.setActionToCurrentTurn();
   }
   else
   {
      throw std::runtime_error("Not a conflict type choice!");
   }
}

std::string l5r::getConflictTypeName(conflicttype type)
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
