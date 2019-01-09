#ifndef _PHASE_H_
#define _PHASE_H_

namespace l5r
{
   enum class phase
   {
      pregame,
      dynasty,
      draw,
      conflict,
      fate,
      regroup,
      gameover
   };

   enum class subphase
   {
      // pregame
      stronghold_selection,
      dynasty_mulligan,
      conflict_mulligan,

      // dynasty
      dynasty_setup,
      province_play,
      additional_fate,

      //draw
      bid,

      // conflict
      //preconflict
      choose_attackers,
      choose_ring,
      choose_conflicttype,
      choose_province,
      choose_defenders,
      conflict_action,
      choose_favor,
      
      // fate phase and regroup phase
      choose_discard
   };
};

#endif // _PHASE_H_
