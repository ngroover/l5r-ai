#include "drawengine.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace l5r;


drawEngine::drawEngine(std::shared_ptr<engineShared> es) : shared(es)
{
}

drawEngine::~drawEngine()
{
}

void drawEngine::doAction(choice c)
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::bid:
         doBid(c);
         break;
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision drawEngine::getDecision()
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::bid:
         return getBidDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

decision drawEngine::getBidDecision()
{
   std::list<choice> choiceList;
   for (int i=MIN_BID;i <= MAX_BID;i++)
   {
      std::stringstream ss;
      ss << i;
      std::string bidStr;
      ss >> bidStr;
      choice c("Bid "+bidStr, choicetype::bid);
      c.setNumber(i);
      choiceList.push_back(c);
   }
   decision d("Choose an honor bid", choiceList);
   return d;
}

void drawEngine::doBid(choice c)
{
   std::cout << shared->getCurrentPlayer()->getName() << " bid " << c.getNumber() << std::endl;
   playercards &gameCards=shared->getCurrentPlayerCards();
   playercards &opponentCards = shared->getOpponentCards();
   gameCards.honorDial = c.getNumber();
   if(shared->state.currentTurn != shared->state.currentAction)
   {
      exchangeHonor(shared->getOpponentPlayer()->getName(), opponentCards, gameCards);
      exchangeHonor(shared->getCurrentPlayer()->getName(), gameCards, opponentCards);
      drawCards(shared->getCurrentPlayer()->getName(), gameCards, gameCards.honorDial);
      drawCards(shared->getOpponentPlayer()->getName(), opponentCards, opponentCards.honorDial);
      gameCards.availableConflicts.push_back(conflicttype::military);
      gameCards.availableConflicts.push_back(conflicttype::political);
      opponentCards.availableConflicts.push_back(conflicttype::military);
      opponentCards.availableConflicts.push_back(conflicttype::political);
      shared->state.currentPhase = phase::conflict;
      shared->state.currentSubPhase = subphase::choose_attackers;
      shared->state.currentConflict = shared->state.currentTurn;
   }
   shared->swapCurrentActionPlayer();
}

void drawEngine::exchangeHonor(std::string name, playercards &gameCards, playercards &opponentCards)
{
   int honorTransfer = opponentCards.honorDial - gameCards.honorDial;

   //TODO: write a generic shared honor lose function
   if(honorTransfer > 0)
   {
      gameCards.honorTokens += honorTransfer;
      std::cout << name << " gains " << honorTransfer << " honor (" << gameCards.honorTokens << " total)" << std::endl;
   }
   else if(honorTransfer < 0)
   {
      gameCards.honorTokens += honorTransfer;
      std::cout << name << " loses " << -honorTransfer << " honor (" << gameCards.honorTokens << " total)" << std::endl;
   }
}

void drawEngine::drawCards(std::string name, playercards &gameCards, int num)
{
   // TODO: write a generic shared function to draw cards
   auto cd = gameCards.conflict_drawdeck.begin();
   std::cout << name << " draws " << num << " conflict cards" << std::endl;
   for(int i=0;i < num;i++)
   {
      gameCards.conflict_hand.push_back(*cd);
      card &conflictCard = shared->cardList.at(*cd);
      std::cout << " " << conflictCard.getName() <<  std::endl;
      cd = gameCards.conflict_drawdeck.erase(cd);
   }
}
