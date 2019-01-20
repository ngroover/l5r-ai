#include "provincecardmanager.h"
#include <iostream>
#include "state/cardarea.h"

using namespace l5r;


provinceCardManager::provinceCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr):state(state), cardMgr(cardMgr)
{
}

provinceCardManager::~provinceCardManager()
{
}

void provinceCardManager::chooseStronghold(cardarea *cards, int provinceChoice)
{
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov)
   {
      if(prov->provinceCard == provinceChoice)
      {
         cards->provinceArea.erase(prov);
         cards->strongholdProvince = provinceChoice;
         prov = cards->provinceArea.end();
      }
   }
}

int provinceCardManager::getStartingHonor(cardarea *cards)
{
   return cardMgr->getStrongholdHonor(cards->stronghold);
}

std::list<choice> provinceCardManager::getStrongholdChoices(cardarea *cards)
{
   std::list<choice> list;
   for(auto prov:cards->provinceArea)
   {
      choice c(cardMgr->getCardName(prov.provinceCard), choicetype::card);
      c.setNumber(prov.provinceCard);
      list.push_back(c);
   }
   return list;
}

//int provinceCardManager::getStrongholdProvince(cardarea *cards)
//{
   //return ;
//}

