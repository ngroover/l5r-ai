#include "agentmanager.h"

using namespace l5r;

agentManager::agentManager(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2, std::shared_ptr<gamestate> state):player1(std::move(player1)), player2(std::move(player2)), state(state)
{
}

agentManager::~agentManager()
{
}

std::string agentManager::getPlayerName(relativePlayer player)
{
   if(player == relativePlayer::myself)
   {
      if(state->currentAction == player::player1)
      {
         return player1->getName();
      }
      else
      {
         return player2->getName();
      }
   }
   else if(player == relativePlayer::opponent)
   {
      if(state->currentAction == player::player1)
      {
         return player2->getName();
      }
      else
      {
         return player1->getName();
      }
   }
   else
   {
      throw std::runtime_error("Invalid relativeplayer");
   }
}

std::string agentManager::getPlayerName(int playerNum)
{
   switch(playerNum)
   {
      case 1:
         return player1->getName();
      case 2:
         return player2->getName();
      default:
         throw std::runtime_error("Invalid player number");
   }
}

decklist agentManager::getPlayerDecklist(int playerNum)
{
   switch(playerNum)
   {
      case 1:
         return player1->getDeckList();
      case 2:
         return player2->getDeckList();
      default:
         throw std::runtime_error("Invalid player number");
   }
}

choice agentManager::getCurrentPlayerChoice(decision d)
{
   if(state->currentAction == player::player1)
   {
      return player1->chooseAction(d);
   }
   else if(state->currentAction == player::player2)
   {
      return player2->chooseAction(d);
   }
   else
   {
      throw std::runtime_error("Invalid currentAction player");
   }
}
