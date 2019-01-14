#ifndef _TOKENS_H_
#define _TOKENS_H_

#include <boost/serialization/version.hpp>

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

         int honorTokens;
         int fate;
         int honorDial;
   };
};

#endif // _TOKENS_H_
