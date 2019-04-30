#include "mctsactionnode.h"
#include "mctsstatenode.h"

using namespace l5r;

MctsActionNode::MctsActionNode(choice c, double probability, MctsStateNodeWeakPtr parent): c(c),probability(probability), parent(parent)
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

int MctsActionNode::getVisits()
{
   return visits;
}

choice MctsActionNode::getChoice()
{
   return c;
}
