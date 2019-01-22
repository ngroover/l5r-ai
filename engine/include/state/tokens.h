#ifndef _TOKENS_H_
#define _TOKENS_H_

#include <boost/serialization/version.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace l5r
{
   class tokenstate
   {
      public:
         friend class boost::serialization::access;
         template<class Archive>
         void serialize(Archive & ar, const unsigned int version)
         {
            ar & honorTokens;
            ar & fate;
            ar & honorDial;
         }

         tokenstate();
         ~tokenstate();

         friend bool operator==(const tokenstate &ts, const tokenstate &ts2);
         friend bool operator<(const tokenstate &ts, const tokenstate &ts2);

         int honorTokens;
         int fate;
         int honorDial;
   };

   bool operator==(const tokenstate &ts, const tokenstate &ts2);
   bool operator<(const tokenstate &ts, const tokenstate &ts2);
};

#endif // _TOKENS_H_
