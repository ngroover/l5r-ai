#include "gamestateintfc.h"
#include "state/gamestate.h"
#include "state/cardarea.h"
#include "state/conflict.h"

using namespace l5r;

GameStateIntfc::GameStateIntfc(std::shared_ptr<gamestate> ptr, std::string player1Name, std::string player2Name) : state(ptr), player1(player1Name), player2(player2Name)
{
}

GameStateIntfc::~GameStateIntfc()
{
}

tokenstate *GameStateIntfc::getPlayerTokens()
{
   if(state->currentAction == player::player1)
   {
      return &state->player1State.tokens;
   }
   else
   {
      return &state->player2State.tokens;
   }
}

tokenstate *GameStateIntfc::getOpponentTokens()
{
   if(state->currentAction == player::player1)
   {
      return &state->player2State.tokens;
   }
   else
   {
      return &state->player1State.tokens;
   }
}

std::string GameStateIntfc::getPlayerName()
{
   if(state->currentAction == player::player1)
   {
      return player1;
   }
   else
   {
      return player2;
   }
}

std::string GameStateIntfc::getOpponentName()
{
   if(state->currentAction == player::player1)
   {
      return player2;
   }
   else
   {
      return player1;
   }
}

cardarea *GameStateIntfc::getPlayerCards()
{
   if(state->currentAction == player::player1)
   {
      return &state->player1State.cards;
   }
   else
   {
      return &state->player2State.cards;
   }
}

cardarea *GameStateIntfc::getOpponentCards()
{
   if(state->currentAction == player::player1)
   {
      return &state->player2State.cards;
   }
   else
   {
      return &state->player1State.cards;
   }
}


std::string GameStateIntfc::getAttackerName()
{
   if(state->currentConflict == player::player1)
   {
      return player1;
   }
   else
   {
      return player2;
   }
}

std::string GameStateIntfc::getDefenderName()
{
   if(state->currentConflict == player::player1)
   {
      return player2;
   }
   else
   {
      return player1;
   }
}

conflictPlayerState *GameStateIntfc::getAttackerConflictState()
{
   if(state->currentConflict == player::player1)
   {
      return &state->player1State.conflict_state;
   }
   else
   {
      return &state->player2State.conflict_state;
   }
}

conflictPlayerState *GameStateIntfc::getDefenderConflictState()
{
   if(state->currentConflict == player::player1)
   {
      return &state->player2State.conflict_state;
   }
   else
   {
      return &state->player1State.conflict_state;
   }
}

conflictState *GameStateIntfc::getGlobalConflictState()
{
   return &state->conflict_state;
}

std::shared_ptr<gamestate> GameStateIntfc::getState()
{
   return state;
}

cardarea *GameStateIntfc::getAttackerCards()
{
   if(state->currentConflict == player::player1)
   {
      return &state->player1State.cards;
   }
   else
   {
      return &state->player2State.cards;
   }
}

cardarea *GameStateIntfc::getDefenderCards()
{
   if(state->currentConflict == player::player1)
   {
      return &state->player2State.cards;
   }
   else
   {
      return &state->player1State.cards;
   }
}
