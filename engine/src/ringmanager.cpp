#include "ringmanager.h"

using namespace l5r;

ringManager::ringManager(std::shared_ptr<gamestate> state): state(state)
{
}

ringManager::~ringManager()
{
}

void ringManager::setAllUnclaimed()
{
   state->unclaimed_rings.clear();
   state->unclaimed_rings.push_back(ring::air);
   state->unclaimed_rings.push_back(ring::fire);
   state->unclaimed_rings.push_back(ring::earth);
   state->unclaimed_rings.push_back(ring::water);
   state->unclaimed_rings.push_back(ring::_void);
}
