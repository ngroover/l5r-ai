#ifndef _CONFLICT_H_
#define _CONFLICT_H_

#include <list>
#include "state/ring.h"
#include "state/character.h"

namespace l5r
{
   // player specific conflict data
   class conflictPlayerState
   {
   public:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
         ar & BOOST_SERIALIZATION_NVP(inConflict);
         ar & BOOST_SERIALIZATION_NVP(claimed_rings);
         ar & politicalConflictsLeft;
         ar & militaryConflictsLeft;
         ar & totalConflictsLeft;
         ar & numConflicts;
         ar & hasImperialFavor;
      }

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
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
         ar & contested_ring;
         ar & conflict_type;
         ar & contested_province;
         ar & BOOST_SERIALIZATION_NVP(unclaimed_rings);
         ar & favorType;
      }

      conflictState();
      ~conflictState();

      bool operator==(const conflictState &cs);

      // currently contested ring
      ring contested_ring;

      // current conflict type
      conflicttype conflict_type;

      // current contested province
      int contested_province;

      // unclaimed rings
      std::list<unclaimedring> unclaimed_rings;

      conflicttype favorType;
   };
};
#endif // _CONFLICT_H_
