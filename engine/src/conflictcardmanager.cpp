#include "conflictcardmanager.h"
#include <iostream>
#include "state/cardarea.h"
#include "gamestateintfc.h"
#include "carddatamanager.h"
#include "tokenmanager.h"

using namespace l5r;


conflictCardManager::conflictCardManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr):stateIntfc(stateIntfc), cardMgr(cardMgr)
{
}

conflictCardManager::~conflictCardManager()
{
}

void conflictCardManager::drawCards(int numCards, cardarea *cards, tokenManager *tokens, std::string playerName)
{
   if( numCards > 0)
   {
      auto conflictDeckIter=cards->conflictDeck.begin();
      std::cout << playerName
         << " drew" << std::endl;
      for(int i=0;i<numCards;i++)
      {
         if(conflictDeckIter == cards->conflictDeck.end())
         {
            std::cout << "conflict deck empty" << std::endl;
            if(cards->conflictDiscard.size() > 0)
            {
               std::cout << "Reshuffing ocnflict deck" << std::endl;
               cards->conflictDeck = cards->conflictDiscard;
               cards->conflictDiscard.clear();
               tokens->loseHonor(5);
               conflictDeckIter = cards->conflictDeck.begin();
            }
            else
            {
               std::cout << "conflict discard empty!" << std::endl;
               i=numCards;
            }
         }
         if(conflictDeckIter != cards->conflictDeck.end())
         {
            // add to hand
            cards->conflictHand.push_back(*conflictDeckIter);
            std::cout << " " << cardMgr->getCardName(*conflictDeckIter) << std::endl; 

            // erase from deck
            conflictDeckIter = cards->conflictDeck.erase(conflictDeckIter);
         }
      }
   }
}


int conflictCardManager::getNumCards(cardarea *cards)
{
   return cards->conflictHand.size();
}
