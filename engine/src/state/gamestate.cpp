#include "state/gamestate.h"

using namespace l5r;

gamestate::gamestate()
{
}

gamestate::~gamestate()
{
}

bool gamestate::operator==(const gamestate &gs)
{
   // assume all the card ids are the same to get some performance for comparision
   // this only works if all simulations are done with the same decks
   return (currentPhase == gs.currentPhase &&
      currentSubPhase == gs.currentSubPhase &&
      currentTurn == gs.currentTurn &&
      currentConflict == gs.currentConflict &&
      currentAction == gs.currentAction &&
      winner == gs.winner &&
      player1State == gs.player1State &&
      player2State == gs.player2State &&
      conflict_state == gs.conflict_state);
}

