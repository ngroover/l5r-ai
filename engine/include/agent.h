#ifndef _AGENT_H_
#define _AGENT_H_

#include <string>
#include <decklist.h>
#include "choice.h"
#include "decision.h"

namespace l5r
{
   class agent
   {
      public:
         agent(std::string name, Decklist deck);
         ~agent();

         std::string getName();
         Decklist getDeckList();

         virtual choice chooseAction(decision d) = 0;

      private:
         std::string name;
         Decklist deck;
   };
}

#endif //_AGENT_H_
