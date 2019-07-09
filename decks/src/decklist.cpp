#include "decklist.h"

using namespace l5r;

Decklist::Decklist(std::string name, std::vector<std::string> cardList)
{
   this->name = name;
   this->cardList = cardList;
}

Decklist::~Decklist()
{
}

std::string Decklist::getName() const
{
   return name;
}

std::vector<std::string> Decklist::getList() const
{
   return cardList;
}

