#include "cpuagent.h"
#include <iostream>

using namespace l5r;

cpuagent::cpuagent(std::string name, decklist deck) :
   agent(name, deck)
{
}

cpuagent::~cpuagent()
{
}

choice cpuagent::chooseAction(decision d)
{
   std::random_device r;
   std::mt19937 gen(r());
   std::uniform_int_distribution<int> dist(1,d.getChoiceList().size());
   int choice = dist(gen);

   for(auto ch : d.getChoiceList() )
   {
      if (--choice == 0)
      {
         return ch;
      }
   }
}
