#ifndef _GLOBAL_SLOT_H_
#define _GLOBAL_SLOT_H_

namespace l5r
{
   struct GlobalSlot
   {
      // phase
      double pregame;
      double dynasty;
      double draw;
      double conflict;
      double fate;
      double regroup;
      // gameover excluded

      // subphase
      double stronghold_selection;
      double dynasty_mulligan;
      double conflict_mulligan;
      double dynasty_setup;
      double province_play;
      double additional_fate;
      double bid;
      double choose_attackers;
      double choose_ring;
      double choose_conflicttype;
      double choose_defenders;
      double conflict_action;
      double choose_favor;
      double choose_discard;

      // turn states
      double player1_turn;
      double player1_conflict;
      double player1_action;
      double player2_turn;
      double player2_conflict;
      double player2_action;

      // random state info
      double conflictMil; // probably move to ring someday
      double conflictPol; // probably move to ring someday
      double favorMil;
      double favorPol;
   } typedef GlobalSlot;
}
#endif // _GLOBAL_SLOT_H_
