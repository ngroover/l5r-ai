#include "decklist.h"

using namespace l5r;

decklist::decklist(std::string name, std::list<cards> cardList)
{
   this->name = name;
   this->cardList = cardList;
}

decklist::~decklist()
{
}

std::string decklist::getName()
{
   return name;
}

std::list<cards> decklist::getList()
{
   return cardList;
}

