#include "choicesimulation.h"
#include <iostream>

using namespace l5r;

void choiceSimulation(std::list<choice> choiceList, engine *eng)
{
   auto overallChoiceList = choiceList.begin();
   while(overallChoiceList != choiceList.end())
   {
      decision d = eng->getDecision();

      auto currentChoiceList = d.getChoiceList().begin();
      auto matchedChoice = d.getChoiceList().end();
      while( currentChoiceList != d.getChoiceList().end())
      {
         std::cout << currentChoiceList->getText() << std::endl;
         if(currentChoiceList->getType() == overallChoiceList->getType() &&
            currentChoiceList->getText() == overallChoiceList->getText())
         {
            matchedChoice = currentChoiceList;
         }
         currentChoiceList++;
      }

      if(matchedChoice == d.getChoiceList().end())
      {
         throw std::runtime_error("Choice " + overallChoiceList->getText() + " not available!");
      }

      eng->doAction(*matchedChoice);

      overallChoiceList++;
   }
}

void printChoices(engine *eng)
{
   decision d = eng->getDecision();
   std::cout << "Choices:" << std::endl;
   auto currentChoiceList = d.getChoiceList().begin();
   while( currentChoiceList != d.getChoiceList().end())
   {
      std::cout << currentChoiceList->getText() << std::endl;
      currentChoiceList++;
   }
   std::cout << std::endl;
}
