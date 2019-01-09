#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <boost/serialization/version.hpp>
#include "state/province.h"
#include "state/character.h"
#include "state/conflict.h"

namespace l5r
{
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
};

#endif // _PLAYER_H_
