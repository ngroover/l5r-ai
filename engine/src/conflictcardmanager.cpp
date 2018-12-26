#include "conflictcardmanager.h"
#include <iostream>

using namespace l5r;


conflictCardManager::conflictCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr, std::shared_ptr<agentManager> agentMgr):state(state), cardMgr(cardMgr), agentMgr(agentMgr)
{
}

conflictCardManager::~conflictCardManager()
{
}

void conflictCardManager::createDeck(decklist deck, int playerNum)
{
   // shouldn't be cards here but clear just in case
   state->getPlayerState(playerNum).conflictDeck.clear();

   for(auto c: deck.getList())
   {
      if(cardMgr->getCardType(c) == cardtype::conflict)
      {
         // add to global table for unique id
         state->cardIds.push_back(c);
         
         // add card to deck
         state->getPlayerState(playerNum).conflictDeck.push_back(state->cardIds.size() - 1);
      }
   }
}

void conflictCardManager::drawCards(int numCards, playerstate &pState, std::string playerName)
{
   if( numCards > 0)
   {
      auto conflictDeckIter=pState.conflictDeck.begin();
      std::cout << playerName
         << " drew" << std::endl;
      for(int i=0;i<numCards;i++)
      {
         // add to hand
         pState.conflictHand.push_back(*conflictDeckIter);
         std::cout << " " << cardMgr->getCardName(*conflictDeckIter) << std::endl; 

         // erase from deck
         conflictDeckIter = pState.conflictDeck.erase(conflictDeckIter);
      }
   }
}

void conflictCardManager::chooseMulliganCard(int cardChoice)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   for(auto conf=pState.conflictHand.begin();conf!=pState.conflictHand.end();++conf)
   {
      if(*conf == cardChoice)
      {
         // add to pending mulligan
         pState.pendingMulligan.push_back(*conf);

         // remove from hand
         pState.conflictHand.erase(conf);

         // set iterator to end to end loop
         conf = pState.conflictHand.end();
      }
   }
}

void conflictCardManager::performMulligan()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::cout << agentMgr->getPlayerName(relativePlayer::myself)
      << " mulligans:" << std::endl;
   if(pState.pendingMulligan.size() == 0)
   {
      std::cout << "Nothing" << std::endl;
   }
   else
   {
      for(auto mul: pState.pendingMulligan)
      {
         pState.conflictDeck.push_back(mul);
         std::cout << " " << cardMgr->getCardName(mul) << std::endl;
      }
   }
   pState.pendingMulligan.clear();
}

std::list<choice> conflictCardManager::getConflictCardChoices()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list;
   for(auto conf:pState.conflictHand)
   {
      choice c(cardMgr->getCardName(conf), choicetype::card);
      c.setNumber(conf);
      list.push_back(c);
   }
   return list;
}

int conflictCardManager::getNumCards()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   return pState.conflictHand.size();
}
