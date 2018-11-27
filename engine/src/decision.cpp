#include "decision.h"

using namespace l5r;

decision::decision(std::string prompt, std::list<choice> choiceList)
: prompt(prompt), choiceList(choiceList)
{
}

decision::~decision()
{
}

std::list<choice> &decision::getChoiceList()
{
   return choiceList;
}

std::string &decision::getPrompt()
{
   return prompt;
}
