#ifndef _RING_H_
#define _RING_H_

#include <boost/serialization/version.hpp>
#include <string>

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

      unclaimedring();
      ~unclaimedring();

      friend bool operator<(const unclaimedring &uc, const unclaimedring &uc2);
      friend bool operator==(const unclaimedring &uc, const unclaimedring &uc2);

      ring type;
      int fate;
   };

   bool operator<(const unclaimedring &uc, const unclaimedring &uc2);
   bool operator==(const unclaimedring &uc, const unclaimedring &uc2);

   extern std::string getConflictTypeName(conflicttype type);
   extern std::string getRingName(ring r);
};

#endif // _RING_H_
