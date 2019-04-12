#include "state/tokens.h"

using namespace l5r;

tokenstate::tokenstate()
{
   honorTokens=0;
   fate=0;
   honorDial=0;
}

tokenstate::~tokenstate()
{
}

bool l5r::operator==(const tokenstate &ts, const tokenstate &ts2)
{
   return (ts.honorTokens == ts2.honorTokens &&
      ts.fate == ts2.fate &&
      ts.honorDial == ts2.honorDial);
}

bool l5r::operator<(const tokenstate &ts, const tokenstate &ts2)
{
   return (ts.honorTokens < ts2.honorTokens &&
      ts.fate < ts2.fate &&
      ts.honorDial < ts2.honorDial);
}
