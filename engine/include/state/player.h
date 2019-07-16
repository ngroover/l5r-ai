#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "state/conflict.h"
#include "state/tokens.h"
#include "state/cardarea.h"

namespace l5r
{
   enum class player
   {
      player1,
      player2
   };

   enum class relativePlayer
   {
      myself,
      opponent
   };

   class playerstate
   {
      public:
         playerstate();
         ~playerstate();

//         bool operator==(const playerstate &ps);

         cardarea cards;
         conflictPlayerState conflict_state;

         tokenstate tokens;
         bool passed;
   };
};

#endif // _PLAYER_H_
