#ifndef _RING_SLOT_H_
#define _RING_SLOT_H_

namespace l5r
{
   struct RingSlot
   {
      double player1_claimed;
      double player2_claimed;
      double contested;
      double unclaimed;
   } typedef RingSlot;
}

#endif // _RING_SLOT_H_
