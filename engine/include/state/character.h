#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <boost/serialization/version.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

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

      inplaycharacter();
      ~inplaycharacter();

      friend bool operator==(const inplaycharacter &ipc, const inplaycharacter &ipc2);
      friend bool operator<(const inplaycharacter &ipc, const inplaycharacter &ipc2);

      int characterCard;
      bool bowed;
      int fateAttached;
   };
   bool operator==(const inplaycharacter &ipc, const inplaycharacter &ipc2);
   bool operator<(const inplaycharacter &ipc, const inplaycharacter &ipc2);
};
#endif // _CHARACTER_H_
