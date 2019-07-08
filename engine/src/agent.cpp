#include "agent.h"

using namespace l5r;

agent::agent(std::string name, Decklist deck) :
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

Decklist agent::getDeckList()
{
   return deck;
}
