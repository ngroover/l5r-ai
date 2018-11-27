#include "agent.h"

using namespace l5r;

agent::agent(std::string name, decklist deck) :
   name(name), deck(deck)
{
}

agent::~agent()
{
}

std::string agent::getName()
{
   return name;
}

decklist agent::getDeckList()
{
   return deck;
}
