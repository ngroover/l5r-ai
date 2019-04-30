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
   numCardsChoices = state->cardIds.size();

   // 5 ring choices
   ringChoicesOffset = numCardsChoices;

   // military/political
   conflictTypesChoices = ringChoicesOffset+5; // add 5 rings

   // bids, fate, 
   genericNumberChoicesOffset = conflictTypesChoices+2; // add 2 for conflict Choices

   passChoiceOffset = genericNumberChoicesOffset+50; // add 50 generic number choices

   // add 1 pass choice
   int totalChoices = passChoiceOffset+1;


   // create builder
   builder = new PolicyBuilder(totalChoices);
}

const int PolicyEncoder::getTotalSize()
{
   return builder->getTotalSize();
}

void PolicyEncoder::encode(PolicyList pol, double *networkOutput, int size)
{
   std::map<int, double> polMap;
   for( auto p : pol)
   {
      int choiceNum = choiceToNumber(p.c);

      polMap.insert(
         std::pair<int, double>(choiceNum, p.prob));
   }

   builder->setPolicy(polMap);

   double *rawData = builder->getRawData();

   for(int i=0;i < size; i++)
   {
      networkOutput[i] = rawData[i];
   }
}

// transforms doubles into choice list
void PolicyEncoder::decode(PolicyList &outputPolicy, double *networkOutput, int size)
{
   std::list<int> validBuilderChoices;
   for( auto op : outputPolicy )
   {
      int choiceNum = choiceToNumber(op.c);
      
      validBuilderChoices.push_back(choiceNum);
   }

   double *rawData = builder->getRawData();

   for(int i=0;i < size; i++)
   {
      rawData[i] = networkOutput[i];
   }

   auto polMap = builder->getPolicy(validBuilderChoices);
   
   for( auto &ch : outputPolicy )
   {
      int choiceNum = choiceToNumber(ch.c);
      
      double prob = polMap[choiceNum];
      std::cout << "raw prob " << prob << std::endl;
      ch.prob = prob;
   }
}

int PolicyEncoder::choiceToNumber(choice c)
{
   int choiceNum = -1;
   switch(c.getType())
   {
      // TODO: condense all the choices to just card
      case choicetype::card:
      case choicetype::province_play:
      case choicetype::province_attack:
         choiceNum = c.getNumber();
         break;
      case choicetype::ring:
         switch(c.getChosenRing())
         {
            case ring::air:
               choiceNum = ringChoicesOffset;
               break;
            case ring::fire:
               choiceNum = ringChoicesOffset+1;
               break;
            case ring::earth:
               choiceNum = ringChoicesOffset+2;
               break;
            case ring::water:
               choiceNum = ringChoicesOffset+3;
               break;
            case ring::_void:
               choiceNum = ringChoicesOffset+4;
               break;
         }
         break;
      case choicetype::conflict_type:
         switch(c.getConflictType())
         {
            case conflicttype::military:
               choiceNum = conflictTypesChoices;
               break;
            case conflicttype::political:
               choiceNum = conflictTypesChoices+1;
               break;
         }
         break;
      case choicetype::bid:
      case choicetype::fate:
         choiceNum = genericNumberChoicesOffset+c.getNumber();
         break;
      case choicetype::pass:
         choiceNum = passChoiceOffset;
         break;
       default:
         std::cout << "Invalid choice type" << std::endl;
         break;
   }
   return choiceNum;
}

Policy::Policy(choice c) : c(c)
{
   prob = 0.0;
}

Policy::~Policy()
{
}
