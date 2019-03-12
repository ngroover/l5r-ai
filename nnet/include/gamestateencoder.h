#ifndef _GAMESTATE_ENCODER_H_
#define _GAMESTATE_ENCODER_H_

#include <map>

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

         int encodeCardStates(gamestate *state, double *networkInput);
   };
};

#endif // _GAMESTATE_ENCODER_H_
