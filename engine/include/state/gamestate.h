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

#include "state/phase.h"
#include "state/ring.h"
#include "state/province.h"
#include "state/character.h"
#include "state/conflict.h"
#include "state/player.h"

#define NUM_PROVINCES 5
#define NUM_DYNASTY_PROVINCES 4
#define STARTING_NUM_CONFLICT_CARDS 4
// TODO: make this part of the stronghold card
#define STRONGHOLD_FATE 7
#define MAX_BID 5
#define MIN_BID 1

namespace l5r
{

   class gamestate
   {
      public:
         gamestate(){};
         ~gamestate(){};

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
   };
};
BOOST_CLASS_VERSION(l5r::gamestate, 1);

#endif //_GAMESTATE_H_
