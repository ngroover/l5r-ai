#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include <vector>
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
      choose_conflicttype,
      choose_province,
      choose_defenders,
      conflict_action
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

   class provinceStack
   {
      public:
         int provinceCard;
         int dynastyCard;
         bool facedownDynasty;
   };

   class playerstate
   {
      public:
         // all these integers are referencing cardIds (below)
         std::list<int> dynastyDeck;
         std::list<int> conflictDeck;
         std::list<int> conflictHand;
         std::list<int> pendingMulligan;
         int pendingFateCard; // card awaiting fate
         std::list<provinceStack> provinceArea;
         int strongholdProvince;
         int stronghold;
         std::list<int> atHome;
         std::list<int> inConflict;

         int honorTokens;
         int fate;
         bool passed;
         int honorDial;

         std::list<conflicttype> availableConflicts;
         std::list<conflictring> claimedRings;
   };

   class gamestate
   {
      public:
         gamestate();
         ~gamestate();

         // global card ids
         std::vector<cards> cardIds;

         phase currentPhase;
         subphase currentSubPhase;
         player currentTurn;
         player currentConflict;
         player currentAction;
         playerstate player1State;
         playerstate player2State;

         std::list<ring> unclaimed_rings;
         conflictring contested_ring;
         int contested_province;

         // dynamically get playerstate
         playerstate &getPlayerState(int playerNum);
         playerstate &getPlayerState(relativePlayer rp);
   };
};

#endif //_GAMESTATE_H_
