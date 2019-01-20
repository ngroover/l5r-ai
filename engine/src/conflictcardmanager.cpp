#include "conflictcardmanager.h"
#include <iostream>
#include "state/cardarea.h"
#include "gamestateintfc.h"
#include "carddatamanager.h"

using namespace l5r;


conflictCardManager::conflictCardManager(std::shared_ptr<GameStateIntfc> stateIntfc, std::shared_ptr<cardDataManager> cardMgr):stateIntfc(stateIntfc), cardMgr(cardMgr)
{
}

conflictCardManager::~conflictCardManager()
{
}

void conflictCardManager::drawCards(int numCards, cardarea *cards, std::string playerName)
{
   if( numCards > 0)
   {
      auto conflictDeckIter=cards->conflictDeck.begin();
      std::cout << playerName
         << " drew" << std::endl;
      for(int i=0;i<numCards;i++)
      {
         // add to hand
         if(conflictDeckIter != cards->conflictDeck.end())
         {
            cards->conflictHand.push_back(*conflictDeckIter);
            std::cout << " " << cardMgr->getCardName(*conflictDeckIter) << std::endl; 

            // erase from deck
            conflictDeckIter = cards->conflictDeck.erase(conflictDeckIter);
         }
         else
         {
            std::cout << "conflict deck empty" << std::endl;
         }
      }
   }
}


int conflictCardManager::getNumCards(cardarea *cards)
{
   return cards->conflictHand.size();
}
