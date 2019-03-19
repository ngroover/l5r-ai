#ifndef _GAMESTATE_ENCODER_H_
#define _GAMESTATE_ENCODER_H_

#include <map>
#include "cards.h"

namespace l5r
{
   class gamestate;
   class GamestateEncoder
   {
      public:
         GamestateEncoder();
         ~GamestateEncoder();

         void setupMap(gamestate *state );

         void encode(gamestate *state, double *networkInput, int size);

      private:
         static const int state_input_size;

         std::map<int, int> characterMap;

         // major hack for now.  need to interact with carddata to detect character
         bool checkIfCharacter(cards c);

         int encodeCardStates(gamestate *state, double *networkInput);
   };
};

#endif // _GAMESTATE_ENCODER_H_
