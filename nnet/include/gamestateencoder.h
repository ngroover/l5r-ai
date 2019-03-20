#ifndef _GAMESTATE_ENCODER_H_
#define _GAMESTATE_ENCODER_H_

#include <map>
#include "cards.h"

namespace l5r
{
   class gamestate;
   class GamestateBuilder;
   class GamestateEncoder
   {
      public:
         GamestateEncoder();
         ~GamestateEncoder();

         void setupMap(gamestate *state);

         int getTotalSize();

         void encode(gamestate *state, double *networkInput, int size);

      private:
         GamestateBuilder *builder;

         static const int state_input_size;

         std::map<int, int> characterMap;
         std::map<int, int> holdingMap;
         std::map<int, int> provinceMap;

         // major hack for now.  need to interact with carddata to detect character
         bool checkIfCharacter(cards c);

         bool checkIfHolding(cards c);

         bool checkIfProvince(cards c);

         void encodeCardStates(gamestate *state, double *networkInput);
   };
};

#endif // _GAMESTATE_ENCODER_H_
