#include "policyencoder.h"
#include "policybuilder.h"
#include <iostream>

using namespace l5r;

PolicyEncoder::PolicyEncoder()
{
   builder = NULL;
}

PolicyEncoder::~PolicyEncoder()
{
   if(builder != NULL)
   {
      delete builder;
   }
}

void PolicyEncoder::setupMap(gamestate *state)
{
   // as far as choices go most of them are
   // generic numbers but it may be beneficial
   // to create a range for cards themselves

   // num card choices
   int numCardsChoices = state->cardIds.size();
   std::cout << "Num cards" << numCardsChoices << std::endl;

   // 5 ring choices
   int ringChoices = 5;

   // military/political
   int conflictTypeChoices = 2;

   // bids, fate, 
   int genericNumberChoices = 50;

   // pass choice
   int passChoice = 1;

   int totalChoices = numCardsChoices +
                     ringChoices +
                     conflictTypeChoices +
                     genericNumberChoices +
                     passChoice;

   std::cout << "Creating policy encoder with " << totalChoices << std::endl;

   // create builder
   builder = new PolicyBuilder(totalChoices);
}

const int PolicyEncoder::getTotalSize()
{
   return builder->getTotalSize();
}

void PolicyEncoder::encode(policyMap pol, double *networkOutput, int size)
{
}

// transforms doubles into choice list
void PolicyEncoder::decode(std::list<choice>, double *networkOutput, int size)
{
}

