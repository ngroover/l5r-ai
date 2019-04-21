#include "mctsstatenode.h"
#include "mctsactionnode.h"

using namespace l5r;

MctsStateNode::MctsStateNode(gamestate &gs)
{
   state = gs;
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


