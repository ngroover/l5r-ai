#include "gamestateintfc.h"
#include "state/gamestate.h"

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
