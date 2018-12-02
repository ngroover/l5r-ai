#include "choice.h"

using namespace l5r;

choice::choice(std::string text, choicetype type) :
text(text), type(type)
{
}

choice::~choice()
{
}

choicetype choice::getType() const
{
   return type;
}

std::string choice::getText() const
{
   return text;
}

void choice::setTargetCard(cards target)
{
   targetCard = target;
}

cards choice::getTargetCard() const
{
   return targetCard;
}

void choice::setNumber(int number)
{
   this->number = number;
}

int choice::getNumber() const
{
   return number;
}
