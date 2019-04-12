#include "state/conflict.h"
#include <set>

using namespace l5r;

conflictPlayerState::conflictPlayerState()
{
   politicalConflictsLeft = 0;
   militaryConflictsLeft = 0;
   totalConflictsLeft = 0;
   numConflicts = 0;
}

conflictPlayerState::~conflictPlayerState()
{
}

bool conflictPlayerState::operator==(const conflictPlayerState &cps)
{
   std::set<inplaycharacter> inConflictSet(inConflict.begin(), inConflict.end());   
   std::set<inplaycharacter> CpsInConflictSet(cps.inConflict.begin(), cps.inConflict.end());   
   std::set<ring> claimedRingSet(claimed_rings.begin(), claimed_rings.end());
   std::set<ring> CpsClaimedRingSet(cps.claimed_rings.begin(), cps.claimed_rings.end());

   return (inConflictSet == CpsInConflictSet &&
      claimedRingSet == CpsClaimedRingSet &&
      politicalConflictsLeft == cps.politicalConflictsLeft &&
      militaryConflictsLeft == cps.militaryConflictsLeft &&
      totalConflictsLeft == cps.totalConflictsLeft &&
      hasImperialFavor == cps.hasImperialFavor);
}

conflictState::conflictState()
{
}

conflictState::~conflictState()
{
}

bool conflictState::operator==(const conflictState &cs)
{
   std::set<unclaimedring> unclaimedSet(unclaimed_rings.begin(), unclaimed_rings.end());
   std::set<unclaimedring> CsUnclaimedSet(cs.unclaimed_rings.begin(), cs.unclaimed_rings.end());

   return (contested_ring == cs.contested_ring &&
      conflict_type == cs.conflict_type &&
      contested_province == cs.contested_province &&
      unclaimedSet == CsUnclaimedSet &&
      favorType == cs.favorType);
}
