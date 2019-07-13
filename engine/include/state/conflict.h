#ifndef _CONFLICT_H_
#define _CONFLICT_H_

#include <list>
#include "state/ring.h"
#include "state/character.h"
#include "card.h"

namespace l5r
{
   // player specific conflict data
   class conflictPlayerState
   {
   public:
      conflictPlayerState();
      ~conflictPlayerState();

      bool operator==(const conflictPlayerState &cps);


      // list of cards in conflict
      std::list<inplaycharacter> inConflict;

      // conflicts available
      int politicalConflictsLeft;
      int militaryConflictsLeft;
      int totalConflictsLeft;

      // claimed rings
      std::list<ring> claimed_rings;

      // number of conflicts left for this player
      int numConflicts;

      bool hasImperialFavor;
   };

   // global conflict data
   class conflictState
   {
   public:
      conflictState();
      ~conflictState();

      bool operator==(const conflictState &cs);

      // currently contested ring
      ring contested_ring;

      // current conflict type
      conflicttype conflict_type;

      // current contested province
      CardSharedPtr contestedProvince;
      //int contested_province;

      // unclaimed rings
      std::list<unclaimedring> unclaimed_rings;

      conflicttype favorType;
   };
};
#endif // _CONFLICT_H_
