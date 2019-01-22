#include "state/player.h"

using namespace l5r;

playerstate::playerstate()
{
}

playerstate::~playerstate()
{
}

bool playerstate::operator==(const playerstate &ps)
{
   return (cards == ps.cards &&
      conflict_state == ps.conflict_state &&
      tokens == ps.tokens &&
      passed == ps.passed);
}
