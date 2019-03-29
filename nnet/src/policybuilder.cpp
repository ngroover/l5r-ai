#include "policybuilder.h"
#include <iostream>

using namespace l5r;

PolicyBuilder::PolicyBuilder(int totalChoices)
{
   this->totalChoices = totalChoices;

   int bitCount=0;
   int doubleCount=0;
   totalChoices--; // subtract 1 because 0 counts
   while(totalChoices > 0)
   {
      totalChoices = totalChoices >> 1;
      doubleCount += (1 << bitCount);
      bitCount++;
   }


   this->totalBits = bitCount;
   this->totalSize = doubleCount;
   if(bitCount > 0)
   {
      rawData = new double[doubleCount];
   }
   else
   {
      rawData = NULL;
   }
}

PolicyBuilder::~PolicyBuilder()
{
   if(rawData != NULL)
   {
      delete[] rawData;
   }
}

const int PolicyBuilder::getTotalSize()
{
   return totalSize;
}

double *PolicyBuilder::getRawData()
{
   return rawData;
}

int PolicyBuilder::furthestBit(int num)
{
   int furthestBit=0;
   while(num > 0)
   {
      furthestBit++;
      num = num >> 1;
   }
   return furthestBit;
}

void PolicyBuilder::setPolicy(std::map<int, double> &policyMap)
{
   // encode policy into a double array
   int baseArrayOffset=0;
   for(int b=0; b < totalBits; b++)
   {
      double probabilityOfOne=0;
      double probabilityOfZero=0;
      // start masking bits at msb
      int bitmask = (1 << (totalBits - b - 1));  // individual bit in question
      if(b > 0)
      {
         // look at past bits
         for(int pastBits=0;pastBits < (1 << b);pastBits++)
         {
            int pastPattern = pastBits << (totalBits-b);
            int pastMask=0;
            for(int m=0;m < b;m++)
            {
               pastMask |= (1 << (totalBits-m-1));
            }

            probabilityOfZero = 0;
            probabilityOfOne = 0;
            for( auto pol : policyMap )
            {
               if((pol.first & pastMask) == pastPattern)
               {
                  if(pol.first & bitmask)
                  {
                     probabilityOfOne += pol.second;
                  }
                  else
                  {
                     probabilityOfZero += pol.second;
                  }
               }
            }
            if(probabilityOfZero + probabilityOfOne == 0.0)
            {
               rawData[baseArrayOffset+pastBits] = 0.0;
            }
            else
            {
               rawData[baseArrayOffset+pastBits] = (probabilityOfOne/(probabilityOfOne+probabilityOfZero));
            }
         }
      }
      else
      {
         for( auto pol : policyMap )
         {
            if(pol.first & bitmask)
            {
               probabilityOfOne += pol.second;
            }
            else
            {
               probabilityOfZero += pol.second;
            }
         }
         rawData[baseArrayOffset] = (probabilityOfOne/(probabilityOfOne+probabilityOfZero));
      }
      baseArrayOffset += (1 << b);
   }
}

std::map<int, double> PolicyBuilder::getPolicy(std::list<int> &validChoices)
{
   std::map<int, double> policy;
   // generate a list of ids with probabilities
   /*
   for ( auto vc : validChoices )
   {
      std::cout << "Calculating " << vc << std::endl;
      double totalPercent=1.0;
      for(int b=0; b < totalSize; b++)
      {
         int mask = (1 << b);
         if( vc & mask )
         {
            std::cout << "bit " << b << " is 1 adding " << rawData[b] << std::endl;
            totalPercent *= rawData[b];
         }
         else
         {
            std::cout << "bit " << b << " is 0 adding " << (1 - rawData[b]) << std::endl;
            totalPercent *= (1.0 - rawData[b]);
         }
      }
      std::cout << "Inserting " << totalPercent<< " percent" << std::endl;
      policy.insert(std::pair<int, double>(vc, totalPercent));
   }

   normalize(policy);
   */

   return policy;
}

void PolicyBuilder::normalize(std::map<int, double> &policy)
{
   double total=0.0;
   for(auto p : policy)
   {
      std::cout << "first = " << p.first << " second = " << p.second << std::endl;
      total += p.second;
   }

   std::cout << "Total " << total << std::endl;
   for( auto &p : policy )
   {
      p.second = p.second / total;
      std::cout << "new first = " << p.first << " second = " << p.second << std::endl;
   }
}

int PolicyBuilder::getPolicyChoice()
{
   // implement
   return 0;
}

