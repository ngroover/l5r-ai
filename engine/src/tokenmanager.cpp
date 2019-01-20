#include "tokenmanager.h"
#include "state/tokens.h"
#include <iostream>
#include <sstream>
#include "endgame.h"

using namespace l5r;

tokenManager::tokenManager(tokenstate *tokens, std::string name) : tokens(tokens), name(name)
{
}

tokenManager::~tokenManager()
{
}

void tokenManager::setHonor(int honor)
{
   tokens->honorTokens = honor;
   std::cout << "Setting " << name << " honor to " << honor << std::endl;
}

void tokenManager::gainFate(int fate)
{
   tokens->fate += fate;
   std::cout << name << " gains " << fate << " fate" << std::endl;
}

void tokenManager::loseFate(int fate)
{
   tokens->fate -= fate;
   std::cout << name << " loses " << fate << " fate" << std::endl;
}

int tokenManager::getFate()
{
   return tokens->fate;
}

void tokenManager::setHonorDial(int honor)
{
   tokens->honorDial = honor;
   std::cout << "Setting " << name << " honor dial to " << honor << std::endl;
}

int tokenManager::getHonorDial()
{
   return tokens->honorDial;
}

void tokenManager::gainHonor(int honor)
{
   tokens->honorTokens += honor;
   std::cout << name << " gains " << honor << " honor (" << tokens->honorTokens << " total)" << std::endl;
   if(tokens->honorTokens > 25)
   {
      tokens->honorTokens = 25;
      throw EndGameException(wintype::honor);
   }
}

void tokenManager::loseHonor(int honor)
{
   tokens->honorTokens -= honor;
   std::cout << name << " loses " << honor << " honor (" << tokens->honorTokens << " total)" << std::endl;
   if(tokens->honorTokens < 0)
   {
      tokens->honorTokens = 0;
      throw EndGameException(wintype::dishonor);
   }
}

int tokenManager::getHonor()
{
   return tokens->honorTokens;
}

bool tokenManager::dishonorLoss()
{
   return tokens->honorTokens == 0;
}

bool tokenManager::honorWin()
{
   return tokens->honorTokens == 25;
}
