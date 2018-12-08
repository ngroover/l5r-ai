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
      bid
   };

   enum class player
   {
      player1,
      player2
   };

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
         int honorTokens;
         int fate;
         bool passFirst;
         int honorDial;
         // dyntasy discard pile
         // conflict deck cards
         // conflict discard pile
         // dynasty province row
         // conflict hand cards
   };

   class gamestate
   {
      public:
         gamestate();
         ~gamestate();

         phase currentPhase;
         subphase currentSubPhase;
         player currentTurn;
         player currentAction;
         playercards player1Cards;
         playercards player2Cards;
   };
};

#endif //_GAMESTATE_H_
