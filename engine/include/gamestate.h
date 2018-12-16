#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include "cards.h"

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
      choose_conflicttype, // TODO: combine with ring
      choose_province,
      choose_defenders,
      conflict_action
   };

   enum class player
   {
      player1,
      player2
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

   // TODO: create some interfaces to manage gamestate
   // DynastyDeckManager
   // ConflictDeckmanager
   // ProvinceManager
   // Tokenmanager
   // RingManager
   // Dialmanager
   // TurnManagement

   class playercards
   {
      public:
         cards stronghold;
         cards strongholdProvince;
         cards province[NUM_PROVINCES];
         std::list<cards> dynasty_drawdeck;
         std::list<cards> conflict_drawdeck;
         cards province_dynasty[NUM_DYNASTY_PROVINCES];
         std::list<cards> conflict_hand;
         bool pending_dynasty_mulligan[NUM_DYNASTY_PROVINCES];
         bool facedown_provinces[NUM_DYNASTY_PROVINCES];
         std::list<cards> pending_conflict_mulligan;
         cards pending_fate_card;// the province from which a dynasty card is to be played. (awaiting fate)
         std::list<cards> at_home_characters;
         std::list<cards> in_conflict_characters;
         int honorTokens;
         int fate;
         bool passFirst;
         int honorDial;
         std::list<conflicttype> availableConflicts;
         std::list<conflictring> claimedrings;
   };

   class gamestate
   {
      public:
         gamestate();
         ~gamestate();

         phase currentPhase;
         subphase currentSubPhase;
         player currentTurn;
         player currentConflict;
         player currentAction;
         playercards player1Cards;
         playercards player2Cards;

         std::list<ring> unclaimed_rings;
         ring contested_ring;
         int contested_province;
         conflicttype currentConflictType;
   };
};

#endif //_GAMESTATE_H_
