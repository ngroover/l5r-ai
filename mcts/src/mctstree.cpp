#include "mctstree.h"
#include "mctsstatenode.h"
#include "mctsguide.h"
#include "engine.h"
#include "mctsactionnode.h"
#include <iostream>
#include "mctsguide.h"

using namespace l5r;

MctsTree::MctsTree(MctsActionBuilderPtr actionBuilder, MctsStateBuilderPtr stateBuilder, enginePtr game, MctsStateNodePtr initial) : 
actionBuilder(std::move(actionBuilder)),
stateBuilder(std::move(stateBuilder)),
game(std::move(game)), initialState(initial),
currentState(initial)
{
}

MctsTree::~MctsTree()
{
}

MctsStateNodePtr MctsTree::getCurrent()
{
   return currentState;
}

void MctsTree::setCurrent(MctsStateNodePtr newState)
{
   currentState = newState;
}


bool MctsTree::traverse(MctsGuidePtr guide)
{
   actionBuilder->buildActions(currentState);

   MctsActionNodePtr chosenAction;

   chosenAction = guide->chooseAction(currentState->getVisits(), currentState->getChildActions());

   //std::cout << "The final choice is " << chosenAction->getChoice().getNumber() << std::endl;
   game->setGameState(currentState->getState());

   game->doAction(chosenAction->getChoice());
   
   gamestate newstate = game->getGameState();

   currentState->addVisit();
   // look through child actions
   bool found = false;
   for ( auto ca : chosenAction->getChildStates() )
   {
      auto caPtr = ca.lock();
      if(caPtr->getState() == newstate)
      {
         //std::cout << "Already reached state before" << std::endl;
         currentState = caPtr;
         found = true;
      }
   }

   if(!found)
   {
      currentState  = stateBuilder->buildState(newstate);
      chosenAction->addChildState(currentState);
   }
   
   chosenAction->addVisit();
   history.push_back(chosenAction);

   return !found;
}

void MctsTree::reset()
{
   currentState = initialState;
}

bool MctsTree::hasReachedLeaf()
{
   return currentState->isLeaf();
}

std::list<MctsActionNodePtr> MctsTree::getHistory()
{
   return history;
}

void MctsTree::setCheckpoint()
{
   checkpt = currentState;
   history.clear();
}

void MctsTree::restoreCheckpoint()
{
   history.clear();
   currentState = checkpt;
}
