#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include <list>
#include "cards.h"

#define NUM_PROVINCES 5
#define NUM_DYNASTY_PROVINCES 4

namespace l5r
{
   enum class phase
   {
      pregame,
      gameover
   };

   enum class subphase
   {
      // pregame
      stronghold_selection,
      dynasty_mulligan,
      conflict_mulligan
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
         std::list<cards> pending_conflict_mulligan;
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
