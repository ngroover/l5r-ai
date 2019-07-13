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

void MulliganManager::chooseDynastyMulligan(int cardChoice)
{
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov)
   {
      if((*prov)->dynastyCard == cardChoice)
      {
         // set no card on top of province
         (*prov)->dynastyCard = -1;
         cards->pendingMulligan.push_back(cardChoice);
      }
   }
}
void MulliganManager::chooseConflictMulligan(int cardChoice)
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
         std::cout << " " << cardMgr->getCardName(mul) << std::endl;
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
         std::cout << " " << cardMgr->getCardName(mul) << std::endl;
      }
   }
   cards->pendingMulligan.clear();
}

std::list<choice> MulliganManager::getConflictMulliganChoices()
{
   std::list<choice> list;
   for(auto conf:cards->conflictHand)
   {
      choice c(cardMgr->getCardName(conf), choicetype::card);
      c.setNumber(conf);
      list.push_back(c);
   }
   return list;
}

std::list<choice> MulliganManager::getDynastyMulliganChoices()
{
   std::list<choice> list;
   for(auto prov:cards->provinceArea)
   {
      if(prov->dynastyCard != -1)
      {
         choice c(cardMgr->getCardName(prov->dynastyCard), choicetype::card);
         c.setNumber(prov->dynastyCard);
         list.push_back(c);
      }
   }
   return list;
}

