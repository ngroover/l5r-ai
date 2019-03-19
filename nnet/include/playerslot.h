#ifndef _PLAYER_SLOT_H_
#define _PLAYER_SLOT_H_

namespace l5r
{
   struct PlayerSlot
   {
      double honor[25];
      double fate[50];

      // remaining conflicts
      // 0, 0.5 or 1 which is 0,1,2 respectively
      double mil_left;
      double pol_left;
      double conflicts_left;

      double hasFavor;
   } typedef PlayerSlot;
}
#endif // _PLAYER_SLOT_H_
