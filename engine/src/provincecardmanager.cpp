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
         std::cout << "TODO: current player"
            << " chose " << cardMgr->getCardName(provinceChoice) 
            << " for a stronghold" << std::endl;
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

std::list<choice> provinceCardManager::getProvinceChoices(cardarea *cards)
{
   std::list<choice> list;
   int brokenCount=0;
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
   return list;
}

void provinceCardManager::breakProvince(cardarea *cards, int cardIndex)
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

int provinceCardManager::getStrongholdProvince(cardarea *cards)
{
   return cards->strongholdProvince;
}

