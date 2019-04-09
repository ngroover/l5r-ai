#ifndef _PLAYER_SLOT_H_
#define _PLAYER_SLOT_H_

namespace l5r
{
   struct PlayerSlot
   {
      double honor[25];
      double fate[50];
      double honorDial[6];

      // remaining conflicts
      double mil_left[2];
      double pol_left[2];
      double conflicts_left[2];

      double hasFavor;
   } typedef PlayerSlot;
}
#endif // _PLAYER_SLOT_H_
