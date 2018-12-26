#include "gamestate.h"
#include <stdexcept>

using namespace l5r;

gamestate::gamestate()
{
}

gamestate::~gamestate()
{
}

playerstate &gamestate::getPlayerState(int playerNum)
{
   switch(playerNum)
   {
      case 1:
         return player1State;
      case 2:
         return player2State;
      default:
         throw std::runtime_error("Invalid player number");
   }
}

playerstate &gamestate::getPlayerState(relativePlayer rp)
{
   if((rp == relativePlayer::myself && currentAction == player::player1) || (rp == relativePlayer::opponent && currentAction == player::player2))
   {
      return player1State;
   }
   else
   {
      return player2State;
   }
}
