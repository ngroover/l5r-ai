#include "humanagent.h"
#include <iostream>

using namespace l5r;

humanagent::humanagent(std::string name, Decklist deck) :
   agent(name, deck)
{
}

humanagent::~humanagent()
{
}

choice humanagent::chooseAction(decision d)
{
   std::cout << d.getPrompt() << std::endl;
   int idx=1;
   int choice=0;
   for (auto ch : d.getChoiceList())
   {
      std::cout << "[" << idx++ << "]. " << ch.getText() << std::endl;
      std::cout << "Number is " << ch.getNumber() << std::endl;
   }
   std::cin >> choice;
   
   // TODO: validate input
   for (auto ch : d.getChoiceList())
   {
      if (--choice == 0)
      {
         return ch;
      }
   }
}


