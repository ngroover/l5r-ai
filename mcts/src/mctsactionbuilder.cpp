#include "mctsactionbuilder.h"

using namespace l5r;

MctsActionBuilder::MctsActionBuilder()
{
}

MctsActionBuilder::~MctsActionBuilder()
{
}

void MctsActionBuilder::buildActions(MctsStateNodePtr stateNode)
{
   if( !stateNode->isLeaf() && !stateNode->hasChildActions() )
   {
   }
}
