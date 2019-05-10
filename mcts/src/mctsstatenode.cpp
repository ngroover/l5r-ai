#include "mctsstatenode.h"
#include "mctsactionnode.h"
#include <iostream>

using namespace l5r;


MctsStateNode::MctsStateNode(gamestate gs, PolicyVector policy, double stateValue, bool leaf) : state(gs), policy(policy), value(stateValue), leaf(leaf)
{
   visits = 0;
}

MctsStateNode::~MctsStateNode()
{
}

bool MctsStateNode::hasChildActions()
{
   return ( childActions.size() != 0 );
}

gamestate MctsStateNode::getState()
{
   return state;
}

bool MctsStateNode::isLeaf()
{
   return leaf;
}

int MctsStateNode::getVisits()
{
   return visits;
}

void MctsStateNode::addChildAction(MctsActionNodePtr child)
{
   childActions.push_back(child);
}

PolicyVector MctsStateNode::getPolicy()
{
   return policy;
}

std::list<MctsActionNodePtr> MctsStateNode::getChildActions()
{
   return childActions;
}

bool MctsStateNode::player1Turn()
{
   return (state.currentAction == player::player1);
}

void MctsStateNode::addVisit()
{
   visits++;
}

double MctsStateNode::getValue()
{
   return value;
}
