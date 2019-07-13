#include "carddatamanager.h"

using namespace l5r;

cardDataManager::cardDataManager(std::shared_ptr<gamestate> state) : state(state)
{
}

cardDataManager::~cardDataManager()
{
}

deckside cardDataManager::getSide(cards c)
{
   return cardMap[c]->side;
}

void cardDataManager::loadDecklist(Decklist dl)
{
   // fill in cardMap
   std::map<cards,CardDataSharedPtr> tmpList = cg.generateCards(dl);
   // merge map
   cardMap.insert(tmpList.begin(), tmpList.end());
}

cardtype cardDataManager::getCardType(cards c)
{
   return cardMap[c]->type;
}

cardtype cardDataManager::getCardTypeFromCard(int index)
{
   return cardMap[state->cardIds[index]]->type;
}

std::string cardDataManager::getCardName(int index)
{
   return cardMap[state->cardIds[index]]->name;
}

/*
int cardDataManager::getStrongholdHonor(int index)
{
   return cardMap[state->cardIds[index]]->strongholdHonor;
}
*/

int cardDataManager::getFateCost(int index)
{
   return cardMap[state->cardIds[index]]->fateCost;
}

int cardDataManager::getMilitaryStr(int index)
{
   return cardMap[state->cardIds[index]]->militarySkill;
}

int cardDataManager::getPoliticalStr(int index)
{
   return cardMap[state->cardIds[index]]->politicalSkill;
}

int cardDataManager::getProvinceStr(int index)
{
   return cardMap[state->cardIds[index]]->provinceStr;
}

int cardDataManager::getGlory(int index)
{
   return cardMap[state->cardIds[index]]->glory;
}

int cardDataManager::getHoldingBonus(int index)
{
   return cardMap[state->cardIds[index]]->holdingBonus;
}

CardSharedPtr cardDataManager::getCard(std::string id)
{
   return cg.getCard(id);
}
