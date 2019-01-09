#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <boost/serialization/version.hpp>

namespace l5r
{
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
};
#endif // _CHARACTER_H_
