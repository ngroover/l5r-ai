#include "carddatamanager.h"

using namespace l5r;

cardDataManager::cardDataManager(std::shared_ptr<gamestate> state) : state(state)
{
}

cardDataManager::~cardDataManager()
{
}

CardSharedPtr cardDataManager::getCard(std::string id)
{
   return cg.getCard(id);
}
