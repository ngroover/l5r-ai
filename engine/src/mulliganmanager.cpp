#include "mulliganmanager.h"
#include <iostream>
#include "state/cardarea.h"
#include "carddatamanager.h"

using namespace l5r;

MulliganManager::MulliganManager(cardarea *cards, std::string name, std::shared_ptr<cardDataManager> cardMgr) : cards(cards), name(name), cardMgr(cardMgr)
{
}

MulliganManager::~MulliganManager()
{
}

void MulliganManager::chooseDynastyMulligan(CardSharedPtr cardChoice)
{
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end() && dynastyArea != cards->dynastyArea.end();++prov,++dynastyArea)
   {
      if((*dynastyArea) == cardChoice)
      {
         // set no card on top of province
         (*dynastyArea) = nullptr;
         cards->pendingMulligan.push_back(cardChoice);
      }
   }
}
void MulliganManager::chooseConflictMulligan(CardSharedPtr cardChoice)
{
   for(auto conf=cards->conflictHand.begin();conf!=cards->conflictHand.end();++conf)
   {
      if(*conf == cardChoice)
      {
         // add to pending mulligan
         cards->pendingMulligan.push_back(*conf);

         // remove from hand
         cards->conflictHand.erase(conf);

         // set iterator to end to end loop
         conf = cards->conflictHand.end();
      }
   }
}

void MulliganManager::performDynastyMulligan()
{
   std::cout << name
      << " mulligans:" << std::endl;
   if( cards->pendingMulligan.size() == 0)
   {
      std::cout << "Nothing" << std::endl;
   }
   else
   {
      for(auto mul: cards->pendingMulligan)
      {
         cards->dynastyDeck.push_back(mul);
         std::cout << " " << mul->data->name << std::endl;
      }
   }
   cards->pendingMulligan.clear();
}

void MulliganManager::performConflictMulligan()
{
   std::cout << name
      << " mulligans:" << std::endl;
   if(cards->pendingMulligan.size() == 0)
   {
      std::cout << "Nothing" << std::endl;
   }
   else
   {
      for(auto mul: cards->pendingMulligan)
      {
         cards->conflictDeck.push_back(mul);
         std::cout << " " << mul->data->name << std::endl;
      }
   }
   cards->pendingMulligan.clear();
}

std::list<choice> MulliganManager::getConflictMulliganChoices()
{
   std::list<choice> list;
   for(auto conf:cards->conflictHand)
   {
      choice c(conf->data->name, choicetype::card);
      c.setCard(conf);
      list.push_back(c);
   }
   return list;
}

std::list<choice> MulliganManager::getDynastyMulliganChoices()
{
   std::list<choice> list;
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov:cards->provinceArea)
   {
      if((*dynastyArea) != nullptr)
      {
         choice c((*dynastyArea)->data->name, choicetype::card);
         c.setCard(*dynastyArea);
         list.push_back(c);
      }
      dynastyArea++;
   }
   return list;
}

