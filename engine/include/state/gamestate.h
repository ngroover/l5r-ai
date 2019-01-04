#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include <vector>
#include "cards.h"
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define NUM_PROVINCES 5
#define NUM_DYNASTY_PROVINCES 4
#define STARTING_NUM_CONFLICT_CARDS 4
// TODO: make this part of the stronghold card
#define STRONGHOLD_FATE 7
#define MAX_BID 5
#define MIN_BID 1

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

   enum class ring
   {
      air,
      fire,
      earth,
      water,
      _void
   };

   enum class conflicttype
   {
      military,
      political
   };

   enum class conflictring
   {
      military_air,
      political_air,
      military_fire,
      political_fire,
      military_earth,
      political_earth,
      military_water,
      political_water,
      military_void,
      political_void,
   };

   enum class provinceCardStatus
   {
      unrevealed,
      revealed,
      broken
   };

   class provinceStack
   {
      public:
         friend class boost::serialization::access;
         template<class Archive>
         void serialize(Archive & ar, const unsigned int version)
         {
            ar & provinceCard;
            ar & dynastyCard;
            ar & facedownDynasty;
            ar & provinceStatus;
         }

         int provinceCard;
         int dynastyCard;
         bool facedownDynasty;
         provinceCardStatus provinceStatus;
   };

   // in play characters
   class inplaycharacter
   {
   public:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
         ar & characterCard;
         ar & bowed;
         ar & fateAttached;
      }

      int characterCard;
      bool bowed;
      int fateAttached;
   };

   class Unclaimedring
   {
   public:
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
         ar & type;
         ar & fate;
      }

      ring type;
      int fate;
   };

   // player specific conflict data
   class conflictPlayerState
   {
   public:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
         ar & BOOST_SERIALIZATION_NVP(inConflict);
         ar & BOOST_SERIALIZATION_NVP(availableConflicts);
         ar & BOOST_SERIALIZATION_NVP(claimed_rings);
         ar & numConflicts;
         ar & hasImperialFavor;
      }

      // list of cards in conflict
      std::list<inplaycharacter> inConflict;

      // conflicts available
      std::list<conflicttype> availableConflicts;

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
      // currently contested ring
      ring contested_ring;

      // current conflict type
      conflicttype conflict_type;

      // current contested province
      int contested_province;

      // unclaimed rings
      std::list<Unclaimedring> unclaimed_rings;

      conflicttype favorType;
   };



   class playerstate
   {
      public:
         friend class boost::serialization::access;
         template<class Archive>
         void serialize(Archive & ar, const unsigned int version)
         {
            ar & BOOST_SERIALIZATION_NVP(dynastyDeck);
            ar & BOOST_SERIALIZATION_NVP(dynastyDiscard);
            ar & BOOST_SERIALIZATION_NVP(conflictDeck);
            ar & BOOST_SERIALIZATION_NVP(conflictHand);
            ar & pendingMulligan;
            ar & pendingFateCard; // card awaiting fate
            ar & provinceArea;
            ar & strongholdProvince;
            ar & stronghold;
            ar & atHome;

            ar & conflict_state;

            ar & honorTokens;
            ar & fate;
            ar & passed;
            ar & honorDial;
         }

         // all these integers are referencing cardIds (below)
         std::list<int> dynastyDeck;
         std::list<int> dynastyDiscard;
         std::list<int> conflictDeck;
         std::list<int> conflictHand;
         std::list<int> pendingMulligan;
         int pendingFateCard; // card awaiting fate
         std::list<provinceStack> provinceArea;
         int strongholdProvince;
         int stronghold;
         std::list<inplaycharacter> atHome;

         conflictPlayerState conflict_state;

         int honorTokens;
         int fate;
         bool passed;
         int honorDial;
   };

   class gamestate
   {
      public:
         gamestate();
         ~gamestate();

         friend class boost::serialization::access;
         template<class Archive>
         void serialize(Archive & ar, const unsigned int version)
         {
            ar & BOOST_SERIALIZATION_NVP(cardIds);
            ar & currentPhase;
            ar & currentSubPhase;
            ar & currentTurn;
            ar & currentConflict;
            ar & currentAction;
            ar & winner;
            ar & player1State;
            ar & player2State;
            ar & conflict_state;
         }

         // global card ids
         std::vector<cards> cardIds;

         phase currentPhase;
         subphase currentSubPhase;
         player currentTurn;
         player currentConflict;
         player currentAction;
         player winner;
         playerstate player1State;
         playerstate player2State;

         conflictState conflict_state;

         // TODO remove this
         // dynamically get playerstate
         playerstate &getPlayerState(int playerNum);
         playerstate &getPlayerState(relativePlayer rp);
   };
};
BOOST_CLASS_VERSION(l5r::gamestate, 1);

#endif //_GAMESTATE_H_
