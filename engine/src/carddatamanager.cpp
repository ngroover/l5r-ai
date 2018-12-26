#include "carddatamanager.h"
#include <iostream>

using namespace l5r;

cardDataManager::cardDataManager(std::shared_ptr<gamestate> state) : state(state)
{
}

cardDataManager::~cardDataManager()
{
}

void cardDataManager::loadDecklist(decklist dl, int playerNum)
{
   // fill in cardMap
   std::map<cards,card> tmpList = cg.generateCards(dl);
   for(auto const& x:tmpList)
   {
      state->cardIds.push_back(x.first);
   }
   // merge map
   cardMap.insert(tmpList.begin(), tmpList.end());
}

cardtype cardDataManager::getCardType(cards c)
{
   return cardMap[c].getType();
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