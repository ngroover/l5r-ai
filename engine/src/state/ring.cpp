#include "state/ring.h"

using namespace l5r;

unclaimedring::unclaimedring()
{
}

unclaimedring::~unclaimedring()
{
}

bool l5r::operator==(const unclaimedring &uc, const unclaimedring &uc2)
{
   return (uc.type == uc2.type && uc.fate == uc2.fate);
}

bool l5r::operator<(const unclaimedring &uc, const unclaimedring &uc2)
{
   return (uc.type < uc2.type && uc.fate < uc2.fate);
}
