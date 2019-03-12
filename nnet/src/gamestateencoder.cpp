#include "gamestateencoder.h"
#include "state/gamestate.h"
#include <iostream>

using namespace l5r;

// TODO: dynamically generate
const int GamestateEncoder::state_input_size = 638;

GamestateEncoder::GamestateEncoder()
{
}

GamestateEncoder::~GamestateEncoder()
{
}

void GamestateEncoder::encode(gamestate *state, double *networkInput, int size)
{
   if(size != state_input_size)
   {
      std::cout << "size does not match expected input size" << std::endl;  
      return;
   }

   //encodeCardState(state, networkInput);
}

int GamestateEncoder::encodeCardStates(gamestate *state, double *networkInput)
{
/*
   int totalSize = state->cardIds.size();

   double *currentPosition = networkInput;
   
   // TODO: take into account duplicate cards
   for(auto c : state->player1State.cards.dynastyDeck)
   {
      currentPosition[in_deck] = 1;
   }
   */
   return 0;
}


