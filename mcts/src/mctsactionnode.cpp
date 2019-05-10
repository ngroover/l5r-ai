#include "mctsactionnode.h"
#include "mctsstatenode.h"
#include <iostream>

using namespace l5r;

MctsActionNode::MctsActionNode(choice c, double probability, MctsStateNodeWeakPtr parent): c(c),probability(probability), parent(parent)
{
   visits=0;
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

void MctsActionNode::addVisit()
{
   visits++;
}

choice MctsActionNode::getChoice()
{
   return c;
}

std::list<MctsStateNodeWeakPtr> MctsActionNode::getChildStates()
{
   return child_states;
}

void MctsActionNode::addChildState(MctsStateNodeWeakPtr node)
{
   child_states.push_back(node);
}

void MctsActionNode::adjustReward(double value)
{
   std::cout << "Action " << c.getText() << std::endl;
   std::cout << "Old value is " << reward << std::endl;
   reward = (visits * reward + value)/(visits+1);
   std::cout << "New value is " << reward << std::endl;
}
