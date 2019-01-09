#ifndef _RING_H_
#define _RING_H_

#include <boost/serialization/version.hpp>

namespace l5r
{
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

   class unclaimedring
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
};

#endif // _RING_H_
