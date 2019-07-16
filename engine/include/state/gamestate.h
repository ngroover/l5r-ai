#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include <vector>

#include "state/phase.h"
#include "state/ring.h"
#include "state/character.h"
#include "state/conflict.h"
#include "state/player.h"

#define NUM_PROVINCES 5
#define NUM_DYNASTY_PROVINCES 4
#define STARTING_NUM_CONFLICT_CARDS 4
// TODO: make this part of the stronghold card
#define STRONGHOLD_FATE 7
#define MAX_BID 5
#define MIN_BID 1

namespace l5r
{

   class gamestate
   {
      public:
         gamestate();
         ~gamestate();



         phase currentPhase;
         subphase currentSubPhase;
         player currentTurn;
         player currentConflict;
         player currentAction;
         player winner;
         playerstate player1State;
         playerstate player2State;

         conflictState conflict_state;
   };
};

#endif //_GAMESTATE_H_
