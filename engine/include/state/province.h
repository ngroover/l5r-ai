#ifndef _PROVINCE_H_
#define _PROVINCE_H_

#include <boost/serialization/version.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace l5r
{
   enum class provinceCardStatus
   {
      unrevealed,
      revealed,
      broken
   };

   class provinceStack
   {
      public:
         friend class boost::serialization::access;
         template<class Archive>
         void serialize(Archive & ar, const unsigned int version)
         {
            ar & provinceCard;
            ar & dynastyCard;
            ar & facedownDynasty;
            ar & provinceStatus;
         }

         provinceStack();
         ~provinceStack();

         friend bool l5r::operator==(const provinceStack &ps, const provinceStack &ps2);

         int provinceCard;
         int dynastyCard;
         bool facedownDynasty;
         provinceCardStatus provinceStatus;
   };
};
#endif // _PROVINCE_H_
