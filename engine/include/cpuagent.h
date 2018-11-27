#ifndef _CPUAGENT_H_
#define _CPUAGENT_H_

#include <string>
#include <random>
#include "decklist.h"
#include "choice.h"
#include "decision.h"
#include "agent.h"

namespace l5r
{
   class cpuagent : public agent
   {
      public:
         cpuagent(std::string name, decklist deck);
         ~cpuagent();

         virtual choice chooseAction(decision d);

      private:
         //std::mt19937 gen;
         //std::random_device r;
   };
}

#endif //_CPUAGENT_H_
