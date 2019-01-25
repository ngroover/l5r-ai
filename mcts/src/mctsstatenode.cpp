#include "mctsstatenode.h"
#include "mctsactionnode.h"

using namespace l5r;

MctsStateNode::MctsStateNode()
{
}

MctsStateNode::~MctsStateNode()
{
}

MctsStateNode::hasChildActions()
{
   return ( childActions.size() != 0 );
}

MctsStateNode::getState()
{
   return state;
}

MctsStateNode::isLeaf()
{
   return isLeaf;
}


