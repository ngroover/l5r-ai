#include "endgame.h"

using namespace l5r;

EndGameException::EndGameException(wintype type) : type(type)
{
}

EndGameException::~EndGameException()
{
}

wintype EndGameException::getType()
{
   return type;
}
