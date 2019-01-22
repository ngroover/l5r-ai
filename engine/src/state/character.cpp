#include "state/character.h"

using namespace l5r;

inplaycharacter::inplaycharacter()
{
}

inplaycharacter::~inplaycharacter()
{
}

bool l5r::operator==(const inplaycharacter &ipc, const inplaycharacter &ipc2)
{
   return (ipc.characterCard == ipc2.characterCard &&
      ipc.bowed == ipc2.bowed &&
      ipc.fateAttached == ipc2.fateAttached);
}

bool l5r::operator<(const inplaycharacter &ipc, const inplaycharacter &ipc2)
{
   return (ipc.characterCard < ipc2.characterCard &&
      ipc.fateAttached < ipc2.fateAttached);
}

