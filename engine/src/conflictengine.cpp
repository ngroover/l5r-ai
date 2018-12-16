#include "conflictengine.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace l5r;


conflictEngine::conflictEngine(std::shared_ptr<engineShared> es) : shared(es)
{
}

conflictEngine::~conflictEngine()
{
}

void conflictEngine::doAction(choice c)
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::choose_attackers:
         doChooseAttackers(c);
         break;
      case subphase::choose_ring:
         doChooseRing(c);
         break;
      case subphase::choose_province:
         doChooseProvince(c);
         break;
      case subphase::choose_conflicttype:
         doChooseConflictType(c);
         break;
      case subphase::choose_defenders:
         doChooseDefenders(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision conflictEngine::getDecision()
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::choose_attackers:
         return getAttackersDecision();
      case subphase::choose_ring:
         return getRingDecision();
      case subphase::choose_province:
         return getProvinceDecision();
      case subphase::choose_conflicttype:
         return getConflictTypeDecision();
      case subphase::choose_defenders:
         return getDefendersDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void conflictEngine::doChooseAttackers(choice c)
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   if(c.getType() == choicetype::card)
   {
      card &dynastyCard = shared->cardList.at(c.getTargetCard());
      std::cout << "Chose to attack with " << 
         dynastyCard.getName() << std::endl;
      for(auto it=gameCards.at_home_characters.begin();it != 
         gameCards.at_home_characters.end();it++)
      {
         if(*it == c.getTargetCard())
         {
            gameCards.in_conflict_characters.push_back(*it);
            gameCards.at_home_characters.erase(it);
            it=gameCards.at_home_characters.end();
         }
      }
   }
   else
   {
      if(gameCards.in_conflict_characters.size() > 0)
      {
         shared->state.currentSubPhase = subphase::choose_ring;
      }
      else
      {
         std::cout << "Pass conflict" << std::endl;
         if(shared->state.currentTurn == shared->state.currentAction)
         {
            shared->swapCurrentActionPlayer();
         }
      }
   }
}

decision conflictEngine::getAttackersDecision()
{
   std::list<choice> choiceList;
   playercards &gameCards=shared->getCurrentPlayerCards();
   for (auto ch: gameCards.at_home_characters)
   {
      card &dynastyCard = shared->cardList.at(ch);
      choice c(dynastyCard.getName(), choicetype::card);
      c.setTargetCard(ch);
      choiceList.push_back(c);
   }
   if(gameCards.in_conflict_characters.size() > 0)
   {
      choiceList.push_back(choice("Done choosing", choicetype::pass));
   }
   else
   {
      choiceList.push_back(choice("Pass Conflict", choicetype::pass));
   }
   decision d("Choose an attacker", choiceList);
   return d;
}

decision conflictEngine::getRingDecision()
{
   std::list<choice> choiceList;
   for(auto r: shared->state.unclaimed_rings)
   {
      choice c(shared->getRingName(r), choicetype::ring);
      c.setChosenRing(r);
      choiceList.push_back(c);
   }
   decision d("Choose a ring", choiceList);
   return d;
}

void conflictEngine::doChooseRing(choice c)
{
   if(c.getType() == choicetype::ring)
   {
      shared->state.contested_ring = c.getChosenRing();
      std::cout << "Chose " << shared->getRingName(c.getChosenRing()) << " Ring" << std::endl;
      shared->state.currentSubPhase = subphase::choose_conflicttype;
   }
   else
   {
      throw std::runtime_error("Invalid choice type");
   }
}

decision conflictEngine::getConflictTypeDecision()
{
   std::list<choice> choiceList;
   playercards &gameCards=shared->getCurrentPlayerCards();
   for(auto r: gameCards.availableConflicts)
   {
      choice c(shared->getConflictTypeName(r), choicetype::conflict_type);
      c.setConflictType(r);
      choiceList.push_back(c);
   }
   decision d("Choose a conflict type", choiceList);
   return d;
}

void conflictEngine::doChooseConflictType(choice c)
{
   if(c.getType() == choicetype::conflict_type)
   {
      shared->state.currentConflictType = c.getConflictType();
      std::cout << "Chose " << shared->getConflictTypeName(c.getConflictType()) << " conflict" << std::endl;
      shared->state.currentSubPhase = subphase::choose_province;
   }
   else
   {
      throw std::runtime_error("Invalid choice type");
   }
}

decision conflictEngine::getProvinceDecision()
{
   playercards &opponentCards = shared->getOpponentCards();
   std::list<choice> choiceList;
   for(int p=0;p < NUM_DYNASTY_PROVINCES;p++)
   {
      card &provinceCard = shared->cardList.at(opponentCards.province[p]);
      choice c(provinceCard.getName(), choicetype::province_attack);
      c.setNumber(p);
      choiceList.push_back(c);
   }
   decision d("Choose a province", choiceList);
   return d;
}

void conflictEngine::doChooseProvince(choice c)
{
   if(c.getType() == choicetype::province_attack)
   {
      playercards &gameCards=shared->getCurrentPlayerCards();
      shared->state.contested_province = c.getNumber();
      playercards &opponentCards = shared->getOpponentCards();
      card &provinceCard = shared->cardList.at(opponentCards.province[c.getNumber()]);
      std::cout << shared->getCurrentPlayer()->getName() << " starting conflict" << std::endl;
      std::cout << "Attackers:" << std::endl;
      int totalStrength=0;
      for(auto ch: gameCards.in_conflict_characters)
      {
         card &character = shared->cardList.at(ch);
         std::cout << " " << character.getName() << std::endl;
         if(shared->state.currentConflictType == conflicttype::military)
         {
            totalStrength += character.getMilitarySkill();
         }
         else if(shared->state.currentConflictType == conflicttype::political)
         {
            totalStrength += character.getPoliticalSkill();
         }
      }
      std::cout << "Ring: " << shared->getRingName(shared->state.contested_ring) << std::endl;
      std::cout << "Type: " << shared->getConflictTypeName(shared->state.currentConflictType) << std::endl;
      std::cout << "Province: " << provinceCard.getName() << std::endl;
      std::cout << "Total Strength: " << totalStrength << std::endl;

      shared->swapCurrentActionPlayer();
      shared->state.currentSubPhase = subphase::choose_defenders;
   }
   else
   {
      throw std::runtime_error("Invalid choice type");
   }
}

void conflictEngine::doChooseDefenders(choice c)
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   playercards &opponentCards=shared->getOpponentCards();
   if(c.getType() == choicetype::card)
   {
      card &dynastyCard = shared->cardList.at(c.getTargetCard());
      std::cout << "Chose to defend with " << 
         dynastyCard.getName() << std::endl;
      for(auto it=gameCards.at_home_characters.begin();it != 
         gameCards.at_home_characters.end();it++)
      {
         if(*it == c.getTargetCard())
         {
            gameCards.in_conflict_characters.push_back(*it);
            gameCards.at_home_characters.erase(it);
            it=gameCards.at_home_characters.end();
         }
      }
   }
   else
   {
      int mytotalStrength=0;
      bool unopposed = false;
      if(gameCards.in_conflict_characters.size() > 0)
      {
         std::cout << "Chose to defend with " << std::endl;
         for(auto it :gameCards.in_conflict_characters)
         {
            card &character = shared->cardList.at(it);
            std::cout << " " << character.getName() << std::endl;
            if(shared->state.currentConflictType == conflicttype::military)
            {
               mytotalStrength += character.getMilitarySkill();
            }
            else if(shared->state.currentConflictType == conflicttype::political)
            {
               mytotalStrength += character.getPoliticalSkill();
            }
         }
         std::cout << "Total Strength: " << mytotalStrength << std::endl;
         shared->state.currentPhase = phase::gameover;

         // figure out conflict
         //shared->state.currentSubPhase = subphase::conflict_action;
      }
      else
      {
         std::cout << "Undefended conflict" << std::endl;
         shared->state.currentPhase = phase::gameover;
         unopposed = true;
         //shared->state.currentSubPhase = subphase::conflict_action;
      }
      int histotalStrength=0;
      for(auto it :opponentCards.in_conflict_characters)
      {
         card &character = shared->cardList.at(it);
         if(shared->state.currentConflictType == conflicttype::military)
         {
            histotalStrength += character.getMilitarySkill();
         }
         else if(shared->state.currentConflictType == conflicttype::political)
         {
            histotalStrength += character.getPoliticalSkill();
         }
      }
      bool wonConflict=false;
      if(histotalStrength >= mytotalStrength)
      {
         std::cout << shared->getOpponentPlayer()->getName() << " won the conflict" << std::endl;
         wonConflict = true;
      }
      else
      {
         std::cout << shared->getCurrentPlayer()->getName() << " won the conflict" << std::endl;
      }
      // erase available conflict
      for(auto it = gameCards.availableConflicts.begin();it != gameCards.availableConflicts.end();++it)
      {
         if(*it == shared->state.currentConflictType)
         {
            opponentCards.availableConflicts.erase(it);
            it = gameCards.availableConflicts.end();
         }
      }
      // claim ring
      for(auto it=shared->state.unclaimed_rings.begin();
         it != shared->state.unclaimed_rings.end();++it)
      {
         if(*it == shared->state.contested_ring)
         {
            if(wonConflict)
            {
               opponentCards.claimedrings.push_back(shared->getConflictRing(*it, shared->state.currentConflictType));
               std::cout << shared->getOpponentPlayer()->getName() << " claimed the  " << shared->getRingName(*it) << " Ring" << std::endl;
            }
            else
            {
               gameCards.claimedrings.push_back(shared->getConflictRing(*it, shared->state.currentConflictType));
               std::cout << shared->getCurrentPlayer()->getName() << " claimed the  " << shared->getRingName(*it) << " Ring" << std::endl;
            }
         }
      }
   }
}

decision conflictEngine::getDefendersDecision()
{
   std::list<choice> choiceList;
   playercards &gameCards=shared->getCurrentPlayerCards();
   for (auto ch: gameCards.at_home_characters)
   {
      card &dynastyCard = shared->cardList.at(ch);
      choice c(dynastyCard.getName(), choicetype::card);
      c.setTargetCard(ch);
      choiceList.push_back(c);
   }
   if(gameCards.in_conflict_characters.size() > 0)
   {
      choiceList.push_back(choice("Done choosing", choicetype::pass));
   }
   else
   {
      choiceList.push_back(choice("Undefended", choicetype::pass));
   }
   decision d("Choose a defender",choiceList);
   return d;
}
