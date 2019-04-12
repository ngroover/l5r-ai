#ifndef _POLICY_ENCODER_H_
#define _POLICY_ENCODER_H_

#include <map>
#include "choice.h"

namespace l5r
{
   class gamestate;
   class PolicyBuilder;
   typedef std::map<choice, double> policyMap;
   class PolicyEncoder
   {
      public:
         PolicyEncoder();
         ~PolicyEncoder();

         void setupMap(gamestate *state);

         const int getTotalSize();

         // transforms choice list into doubles
         void encode(policyMap pol, double *networkOutput, int size);

         // transforms doubles into choice list
         void decode(std::list<choice>, double *networkOutput, int size);

      private:
         PolicyBuilder *builder;
   };
}
#endif // _POLICY_ENCODER_H_
