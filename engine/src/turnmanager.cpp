#include "turnmanager.h"

using namespace l5r;

turnManager::turnManager(std::shared_ptr<gamestate> state): state(state)
{
}

turnManager::~turnManager()
{
}

void turnManager::setCurrentTurnAndAction(int playerNum)
{
   switch(playerNum)
   {
      case 1:
         state->currentAction = player::player1;
         state->currentTurn = player::player1;
         break;
      case 2:
         state->currentAction = player::player2;
         state->currentTurn = player::player2;
         break;
      default:
         throw std::runtime_error("Invalid player number");
   }
}

bool turnManager::ActionAndTurnDiffer()
{
   return (state->currentAction != state->currentTurn);
}

void turnManager::swapAction()
{
   if(state->currentAction == player::player1)
   {
      state->currentAction = player::player2;
   }
   else
   {
      state->currentAction = player::player1;
   }
}

void turnManager::setActionToCurrentTurn()
{
   state->currentAction = state->currentTurn;
}

void turnManager::swapConflict()
{
   if(state->currentConflict == player::player1)
   {
      state->currentConflict = player::player2;
   }
   else
   {
      state->currentConflict = player::player1;
   }
}

void turnManager::passFirstPlayer()
{
   if(state->currentTurn == player::player1)
   {
      state->currentTurn = player::player2;
   }
   else
   {
      state->currentTurn = player::player1;
   }
}

void turnManager::declareWinner()
{
   state->winner = state->currentAction;
}

void turnManager::declareLoser()
{
   if(state->currentAction == player::player1)
   {
      state->winner = player::player2;
   }
   else
   {
      state->winner = player::player1;
   }
}

void turnManager::giveAttackerAction()
{
   state->currentAction = state->currentConflict;
}

void turnManager::giveDefenderAction()
{
   if(state->currentConflict == player::player1)
   {
      state->currentAction = player::player2;
   }
   else
   {
      state->currentAction = player::player1;
   }
}

// passing actions
void turnManager::passAction()
{
   if(state->currentAction == player::player1)
   {
      state->player1State.passed = true;
   }
   else
   {
      state->player2State.passed = true;
   }
}

void turnManager::resetPassed()
{
   state->player1State.passed = false;
   state->player2State.passed = false;
}

bool turnManager::opponentHasPassed()
{
   if(state->currentAction == player::player1)
   {
      return state->player2State.passed;
   }
   else
   {
      return state->player1State.passed;
   }
}
