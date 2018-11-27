#include "engineshared.h"

using namespace l5r;

engineShared::engineShared()
{
}

engineShared::~engineShared()
{
}

std::unique_ptr<agent> &engineShared::getCurrentPlayer()
{
   if(state.currentAction == player::player1)
   {
      return player1;
   }
   else
   {
      return player2;
   }
}

playercards &engineShared::getCurrentPlayerCards()
{
   if( state.currentAction == player::player1 )
   {
      return state.player1Cards;
   }
   else
   {
      return state.player2Cards;
   }
}

playercards &engineShared::getOpponentCards()
{
   if( state.currentAction == player::player1 )
   {
      return state.player2Cards;
   }
   else
   {
      return state.player1Cards;
   }
}
