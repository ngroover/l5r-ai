#ifndef _POLICY_ENCODER_H_
#define _POLICY_ENCODER_H_

#include <map>
#include "choice.h"

namespace l5r
{
   class gamestate;
   class PolicyBuilder;
   //typedef std::map<choice, double> policyMap;
   class Policy
   {
      public:
         Policy(choice c);
         ~Policy();

         choice c;
         double prob;
   };

   typedef std::list<Policy> PolicyList;
   class PolicyEncoder
   {
      public:
         PolicyEncoder();
         ~PolicyEncoder();

         void setupMap(gamestate *state);

         const int getTotalSize();

         // transforms choice list into doubles
         void encode(PolicyList pol, double *networkOutput, int size);

         // transforms doubles into policymap
         void decode(PolicyList &outputPolicy, double *networkOutput, int size);

      private:
         int choiceToNumber(choice c);

         PolicyBuilder *builder;
         int numCardsChoices;
         int ringChoicesOffset;
         int conflictTypesChoices;
         int genericNumberChoicesOffset;
         int passChoiceOffset;
   };
}
#endif // _POLICY_ENCODER_H_
