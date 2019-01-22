#include "state/province.h"

using namespace l5r;

provinceStack::provinceStack()
{
}

provinceStack::~provinceStack()
{
}

bool l5r::operator==(const provinceStack &ps, const provinceStack &ps2)
{
   return (ps.provinceCard == ps2.provinceCard &&
      ps.dynastyCard == ps2.dynastyCard &&
      ps.facedownDynasty == ps2.facedownDynasty &&
      ps.provinceStatus == ps2.provinceStatus);
}
