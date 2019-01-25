#include "mctstree.h"
#include "mctsstatenode.h"

using namespace l5r;

MctsTree::MctsTree()
{
}

MctsTree::~MctsTree()
{
}

void MctsTree::addNewState(MctsStateNodePtr newState)
{
   // TODO check it exists
   globalStateList.push_back(newState);
}

void MctsTree::reset(MctsStateNodePtr root)
{
   currentState = root;
}

MctsStateNodePtr MctsTree::getCurrent()
{
   return currentState;
}

void MctsTree::traverse()
{
   // build actions (with probabilties from network)
   
   // get turn

   // calculate UCT
}
