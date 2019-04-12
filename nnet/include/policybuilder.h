#ifndef _POLICY_BUILDER_H_
#define _POLICY_BUILDER_H_

#include <map>
#include <list>

namespace l5r
{
   class PolicyBuilder
   {
      public:
         PolicyBuilder(int totalChoices);
         ~PolicyBuilder();

         // pass in a list of choice indexes and their probability
         void setPolicy(std::map<int, double> &policyMap);

         double *getRawData();

         const int getTotalSize();

         // get the probabilities from a list of valid actions
         std::map<int, double> getPolicy(std::list<int> &validChoices);

         // randomly get a choice from the current policy
         int getPolicyChoice();

      private:
         int furthestBit(int num);
         int findSlot(int bit);

         double *rawData;
         int totalSize;

         int totalBits;
         int totalChoices;
   };
};

#endif // _POLICY_BUILDER_H_
