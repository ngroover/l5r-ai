#include "tokenmanager.h"
#include <iostream>
#include <sstream>

using namespace l5r;

tokenManager::tokenManager(std::shared_ptr<gamestate> state,
                           std::shared_ptr<cardDataManager> cardMgr) : state(state), cardMgr(cardMgr)
{
}

tokenManager::~tokenManager()
{
}

void tokenManager::setHonor(int honor, int playerNum, std::string playerName)
{
   playerstate &pState = state->getPlayerState(playerNum);
   pState.honorTokens = honor;
   std::cout << "Setting " << playerName << " honor to " << honor << std::endl;
}

void tokenManager::gainFate(int fate, playerstate &pState, std::string playerName)
{
   pState.fate += fate;
   std::cout << playerName << " gains " << fate << " fate" << std::endl;
}

int tokenManager::getFate(playerstate &pState)
{
   return pState.fate;
}

void tokenManager::addFateToCard(playerstate &pState, int cardIndex, int extraFate)
{
   // TODO: actually store fate to card
   int cardfate = cardMgr->getFateCost(cardIndex);
   pState.fate -= (extraFate + cardfate);
   std::cout << "Paying " << cardfate << " for " << cardMgr->getCardName(cardIndex) << " and adding " << extraFate << " fate. (" << pState.fate
      << " fate left)" << std::endl;
}

std::list<choice> tokenManager::getAdditionalFateChoices(playerstate &pState, int cardIndex)
{
   int fateAvailable = pState.fate - cardMgr->getFateCost(cardIndex);
   std::list<choice> list;
   if(fateAvailable < 0)
   {
      throw std::runtime_error("Not enough fate to play card");
   }
   for(int f=0;f<=fateAvailable;f++)
   {
      std::stringstream ss;
      ss << f;
      std::string fateStr;
      ss >> fateStr;
      choice c(fateStr+" fate", choicetype::fate);
      c.setNumber(f);
      list.push_back(c);
   }
   return list;
}

void tokenManager::setHonorDial(int honor, playerstate &pState, std::string playerName)
{
   pState.honorDial = honor;
   std::cout << "Setting " << playerName << " honor dial to " << honor << std::endl;
}

int tokenManager::getHonorDial(playerstate &pState)
{
   return pState.honorDial;
}

void tokenManager::gainHonor(int honor, playerstate &pState, std::string playerName)
{
   pState.honorTokens += honor;
   if(honor > 0)
   {
      std::cout << playerName << " gains " << honor << " honor (" << pState.honorTokens << " total)" << std::endl;
   }
   else
   {
      std::cout << playerName << " losses " << -honor << " honor (" << pState.honorTokens << " total)" << std::endl;
   }
}

int tokenManager::getHonor(playerstate &pState)
{
   return pState.honorTokens;
}
