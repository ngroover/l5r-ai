#include "mctsactionnode.h"
#include "mctsstatenode.h"

using namespace l5r;

MctsActionNode::MctsActionNode(choice c): c(c)
{
}

MctsActionNode::~MctsActionNode()
{
}

double MctsActionNode::getReward()
{
   return reward;
}

double MctsActionNode::getProbability()
{
   return probability;
}

double MctsActionNode::getVisits()
{
   return visits;
}

