#include "mctsstatenode.h"
#include "mctsactionnode.h"

using namespace l5r;

MctsStateNode::MctsStateNode(gamestate &gs, double *policy, int policySize, double value)
{
   state = gs;
   policy = new double[policySize];
   for(int i=0;i < policySize;i++)
   {
      this->policy[i] =  policy[i];
   }
   this->policySize = policySize;
   this->value = value;
}

MctsStateNode::~MctsStateNode()
{
}

bool MctsStateNode::hasChildActions()
{
   return ( childActions.size() != 0 );
}

gamestate &MctsStateNode::getState()
{
   return state;
}

bool MctsStateNode::isLeaf()
{
   return leaf;
}

void MctsStateNode::addChildAction(MctsActionNodePtr child)
{
   childActions.push_back(child);
}

double *MctsStateNode::getPolicy()
{
   return policy;
}

int MctsStateNode::getPolicySize()
{
   return policySize;
}
