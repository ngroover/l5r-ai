#include "mctstree.h"
#include "mctsstatenode.h"
#include "mctsguide.h"
#include "engine.h"
#include "mctsactionnode.h"
#include <iostream>

using namespace l5r;

MctsTree::MctsTree(MctsGuidePtr player1Guide, MctsGuidePtr player2Guide, MctsActionBuilderPtr actionBuilder, MctsStateBuilderPtr stateBuilder, enginePtr game, MctsStateNodePtr initial) : 
player1Guide(std::move(player1Guide)),
player2Guide(std::move(player2Guide)),
actionBuilder(std::move(actionBuilder)),
stateBuilder(std::move(stateBuilder)),
game(std::move(game)), initialState(initial)
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


bool MctsTree::traverse()
{
   actionBuilder->buildActions(currentState);

   // negative value in neural network for player2
   bool negativeValue = !currentState->player1Turn();


   MctsActionNodePtr chosenAction;
   //TODO: pass in the MctsGuide as arg
   if(currentState->player1Turn())
   {
      chosenAction = player1Guide->chooseAction(currentState->getVisits(), currentState->getChildActions(), negativeValue);
   }
   else
   {
      chosenAction = player2Guide->chooseAction(currentState->getVisits(), currentState->getChildActions(), negativeValue);
   }

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
         std::cout << "Already reached state before" << std::endl;
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
