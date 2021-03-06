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

void choice::setNumber(int number)
{
   this->number = number;
}

int choice::getNumber() const
{
   return number;
}

void choice::setChosenRing(ring r)
{
   this->chosenring = r;
}

ring choice::getChosenRing() const
{
   return chosenring;
}

void choice::setConflictType(conflicttype type)
{
   this->conflictType = type;
}

conflicttype choice::getConflictType() const
{
   return conflictType;
}
