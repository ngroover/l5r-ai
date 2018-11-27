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
         agent(std::string name, decklist deck);
         ~agent();

         std::string getName();
         decklist getDeckList();

         virtual choice chooseAction(decision d) = 0;

      private:
         std::string name;
         decklist deck;
   };
}

#endif //_AGENT_H_
