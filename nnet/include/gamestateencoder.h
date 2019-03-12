#ifndef _GAMESTATE_ENCODER_H_
#define _GAMESTATE_ENCODER_H_

namespace l5r
{
   class gamestate;
   class GamestateEncoder
   {
      public:
         GamestateEncoder();
         ~GamestateEncoder();


         void encode(gamestate *state, double *networkInput, int size);

      private:
         static const int state_input_size;

         int encodeCardStates(gamestate *state, double *networkInput);
   };
};

#endif // _GAMESTATE_ENCODER_H_
