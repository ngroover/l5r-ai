#include "conflictmanager.h"
#include <iostream>

using namespace l5r;


conflictManager::conflictManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr):state(state), cardMgr(cardMgr)
{
}

conflictManager::~conflictManager()
{
}

std::string conflictManager::getContestedProvince()
{
   return cardMgr->getCardName(state->contested_province);
}
