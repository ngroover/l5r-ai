#ifndef _AGENT_MANAGER_H_
#define _AGENT_MANAGER_H_

#include "agent.h"
#include <memory>

namespace l5r
{
   class agentManager
   {
      public:
         agentManager(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2, std::shared_ptr<gamestate> state);
         ~agentManager();

         std::string getPlayerName(relativePlayer player);
         std::string getPlayerName(int playerNum);

         decklist getPlayerDecklist(int playerNum);

         choice getCurrentPlayerChoice(decision d);
      private:
         std::unique_ptr<agent> player1,player2;
         std::shared_ptr<gamestate> state;
   };
};

#endif // _AGENT_MANAGER_H_
