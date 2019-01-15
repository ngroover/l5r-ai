#ifndef _CARD_AREA_H_
#define _CARD_AREA_H_

#include <boost/serialization/version.hpp>
#include <boost/serialization/list.hpp>
#include "state/province.h"
#include "state/character.h"

namespace l5r
{
   class cardarea
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
   };
};

#endif // _CARD_AREA_H_

