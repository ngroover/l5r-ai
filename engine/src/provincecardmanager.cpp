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

void provinceCardManager::chooseStronghold(cardarea *cards, CardSharedPtr provinceChoice)
{
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov)
   {
      if((*prov) == provinceChoice)
      {
         cards->strongholdProvince = provinceChoice;
         prov = cards->provinceArea.erase(prov);
      }
   }
}

int provinceCardManager::getStartingHonor(cardarea *cards)
{
   return cards->stronghold->data->strongholdHonor;
}

std::list<choice> provinceCardManager::getStrongholdChoices(cardarea *cards)
{
   std::list<choice> list;
   for(auto prov:cards->provinceArea)
   {
      choice c(prov->data->name, choicetype::card);
      //c.setNumber(prov.provinceCard);
      c.setCard(prov);
      list.push_back(c);
   }
   return list;
}

//int provinceCardManager::getStrongholdProvince(cardarea *cards)
//{
   //return ;
//}

