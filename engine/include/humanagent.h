#ifndef _HUMANAGENT_H_
#define _HUMANAGENT_H_

#include <string>
#include "decklist.h"
#include "choice.h"
#include "decision.h"
#include "agent.h"

namespace l5r
{
   class humanagent : public agent
   {
      public:
         humanagent(std::string name, Decklist deck);
         ~humanagent();

         virtual choice chooseAction(decision d);
   };
}

#endif //_HUMANAGENT_H_
