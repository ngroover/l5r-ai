#include "carddatamanager.h"
#include <iostream>

using namespace l5r;

cardDataManager::cardDataManager(std::shared_ptr<gamestate> state) : state(state)
{
}

cardDataManager::~cardDataManager()
{
}

void cardDataManager::loadDecklist(decklist dl)
{
   // fill in cardMap
   std::map<cards,card> tmpList = cg.generateCards(dl);
   // merge map
   cardMap.insert(tmpList.begin(), tmpList.end());
}

cardtype cardDataManager::getCardType(cards c)
{
   return cardMap[c].getType();
}

dynastycardtype cardDataManager::getDynastyCardType(int index)
{
   return cardMap[state->cardIds[index]].getDynastyType();
}

std::string cardDataManager::getCardName(int index)
{
   return cardMap[state->cardIds[index]].getName();
}

int cardDataManager::getStrongholdHonor(int index)
{
   return cardMap[state->cardIds[index]].getStrongholdHonor();
}

int cardDataManager::getFateCost(int index)
{
   return cardMap[state->cardIds[index]].getFateCost();
}

int cardDataManager::getMilitaryStr(int index)
{
   return cardMap[state->cardIds[index]].getMilitarySkill();
}

int cardDataManager::getPoliticalStr(int index)
{
   return cardMap[state->cardIds[index]].getPoliticalSkill();
}

int cardDataManager::getProvinceStr(int index)
{
   return cardMap[state->cardIds[index]].getProvinceStr();
}

int cardDataManager::getGlory(int index)
{
   return cardMap[state->cardIds[index]].getGlory();
}

int cardDataManager::getHoldingBonus(int index)
{
   return cardMap[state->cardIds[index]].getHoldingBonus();
}
