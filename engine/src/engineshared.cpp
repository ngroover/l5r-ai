#include "engineshared.h"
#include "gamestate.h"

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

std::unique_ptr<agent> &engineShared::getOpponentPlayer()
{
   if(state.currentAction == player::player1)
   {
      return player2;
   }
   else
   {
      return player1;
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

void engineShared::swapCurrentActionPlayer()
{
   if(state.currentAction == player::player1)
   {
      state.currentAction = player::player2;
   }
   else
   {
      state.currentAction = player::player1;
   }
}

int engineShared::getProvinceIndex(cards province, playercards &gameCards)
{
   for(int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      if(province == gameCards.province[i])
      {
         return i;
      }
   }
}

std::string engineShared::getRingName(ring r)
{
   switch(r)
   {
      case ring::air:
         return "Air";
      case ring::fire:
         return "Fire";
      case ring::earth:
         return "Earth";
      case ring::water:
         return "Water";
      case ring::_void:
         return "Void";
      default:
         throw std::runtime_error("Invalid ring");
   }
}

std::string engineShared::getConflictTypeName(conflicttype type)
{
   switch(type)
   {
      case conflicttype::military:
         return "Military";
      case conflicttype::political:
         return "Political";
      default:
         throw std::runtime_error("Invalid conflict type");
   }
}

conflictring engineShared::getConflictRing(ring r, conflicttype ct)
{
   if(ct == conflicttype::military)
   {
      switch(r)
      {
         case ring::fire:
            return conflictring::military_fire;
         case ring::air:
            return conflictring::military_air;
         case ring::water:
            return conflictring::military_water;
         case ring::_void:
            return conflictring::military_void;
         case ring::earth:
            return conflictring::military_earth;
      }
   }
   else
   {
      switch(r)
      {
         case ring::fire:
            return conflictring::political_fire;
         case ring::air:
            return conflictring::political_air;
         case ring::water:
            return conflictring::political_water;
         case ring::_void:
            return conflictring::political_void;
         case ring::earth:
            return conflictring::political_earth;
      }
   }
}
