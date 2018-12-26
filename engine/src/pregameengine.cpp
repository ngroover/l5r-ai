#include "pregameengine.h"
#include "gamestate.h"
#include <algorithm>
#include <iostream>

using namespace l5r;


pregameEngine::pregameEngine(std::shared_ptr<engineShared> es) : shared(es)
{
}

pregameEngine::~pregameEngine()
{
}

decision pregameEngine::strongholdDecision()
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   std::list<choice> choiceList;
   for (int i=0;i<NUM_PROVINCES;i++)
   {
      cards prov = gameCards.province[i];
      choice c(shared->cardList.at(prov).getName(), choicetype::card);
      c.setTargetCard(prov);
      choiceList.push_back(c);
   }
   decision d("Choose a stronghold", choiceList);
   return d;
}

decision pregameEngine::dynastyMulliganDecision()
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   std::list<choice> choiceList;
   for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      cards dynCard = gameCards.province_dynasty[i];
      cards provCard = gameCards.province[i];
      if(!gameCards.pending_dynasty_mulligan[i])
      {
         choice c(shared->cardList.at(dynCard).getName()+" on "+
               shared->cardList.at(provCard).getName(), choicetype::card);
         c.setTargetCard(provCard);
         choiceList.push_back(c);
      }
   }
   choiceList.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to mulligan",choiceList);
   return d;
}

decision pregameEngine::conflictMulliganDecision()
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   std::list<choice> choiceList;
   for ( auto cc : gameCards.conflict_hand )
   {
      card &conflictCard = shared->cardList.at(cc); 
      choice c(conflictCard.getName(), choicetype::card);
      c.setTargetCard(cc);
      choiceList.push_back(c);
   }
   choiceList.push_back(choice("Pass", choicetype::pass));
   decision d("Choose a card to mulligan",choiceList);
   return d;
}

decision pregameEngine::getDecision()
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::stronghold_selection:
         return strongholdDecision();
      case subphase::dynasty_mulligan:
         return dynastyMulliganDecision();
      case subphase::conflict_mulligan:
         return conflictMulliganDecision();
      default:
         throw std::runtime_error("Invalid substate");
   }
}

void pregameEngine::shiftProvinceRow()
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   std::cout << shared->getCurrentPlayer()->getName() << " Province row:" << std::endl;
   int shiftIndex=0;
   for(int p=0;p<NUM_PROVINCES;p++)
   {
      // shift the provinces down to fill in for the stronghold province
      if(shiftIndex != p)
      {
         gameCards.province[shiftIndex] = gameCards.province[p];
      }
      if( gameCards.province[p] != gameCards.strongholdProvince )
      {
         card &provCard = shared->cardList.at(gameCards.province[p]);
         std::cout << " " << provCard.getName() << std::endl;
         shiftIndex++;
      }
   }
}

void pregameEngine::placeDynastyCards(std::string playerName, playercards &gameCards)
{
   // TODO: merge this with the other function that replaces dynasty cards
   auto dd = gameCards.dynasty_drawdeck.begin();
   std::cout << playerName << " places dynasty cards" << std::endl;
   for(int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      gameCards.province_dynasty[i] = *dd;
      card &dynastyCard = shared->cardList.at(*dd);
      card &provinceCard = shared->cardList.at(gameCards.province[i]);
      std::cout << " Placing " << 
         dynastyCard.getName() << " on " <<
         provinceCard.getName() << std::endl;
      dd = gameCards.dynasty_drawdeck.erase(dd);
   }
}

void pregameEngine::doStrongholdSelection(choice c)
{
   playercards &gameCards = shared->getCurrentPlayerCards();
   playercards &opponentCards = shared->getOpponentCards();
   if( c.getType() == choicetype::card )
   {
      gameCards.strongholdProvince = c.getTargetCard();
      card &strongholdCard = shared->cardList.at(c.getTargetCard());
      std::cout << shared->getCurrentPlayer()->getName() << " chose " << strongholdCard.getName() << " as stronghold" << std::endl;
      shiftProvinceRow();

      // switch action
      if (shared->state.currentAction != shared->state.currentTurn)
      {
         // both players draw dynasty cards
         placeDynastyCards(shared->getOpponentPlayer()->getName(), opponentCards);
         placeDynastyCards(shared->getCurrentPlayer()->getName(), gameCards);
         // go to dynasty state
         shared->state.currentSubPhase = subphase::dynasty_mulligan;
      }
      shared->swapCurrentActionPlayer();
   }
   else
   {
      throw std::runtime_error("Not a card choice!");
   }
}

bool pregameEngine::discardDynastyMulligans()
{
   playercards &gameCards = shared->getCurrentPlayerCards();
   std::cout << shared->getCurrentPlayer()->getName() << " mulligans" <<  std::endl;
   bool noMulligans=true;
   for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      if(gameCards.pending_dynasty_mulligan[i])
      {
         noMulligans = false; 
         card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
         // put mulligan cards on the bottom instead of shuffling
         gameCards.dynasty_drawdeck.push_back(gameCards.province_dynasty[i]);
         card &provCard = shared->cardList.at(gameCards.province[i]);
         std::cout << " " << dynastyCard.getName() << " on " << provCard.getName() << std::endl;
      }
      gameCards.facedown_provinces[i] = true;
   }

   if(noMulligans)
   {
      std::cout << " nothing" << std::endl;
   }
   return noMulligans;
}

void pregameEngine::replaceDynastyMulligans()
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   auto dd = gameCards.dynasty_drawdeck.begin();

   std::cout << shared->getCurrentPlayer()->getName() << " draws new dynasty cards" <<  std::endl;
   for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      if(gameCards.pending_dynasty_mulligan[i])
      {
         card &provCard = shared->cardList.at(gameCards.province[i]);
         card &dynastyCard = shared->cardList.at(*dd);
         gameCards.province_dynasty[i] = *dd;
         std::cout << " Placing " << dynastyCard.getName() << " on " << provCard.getName() << std::endl;
         dd = gameCards.dynasty_drawdeck.erase(dd);
      }
   }
}

void pregameEngine::doDynastyMulligan(choice c)
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   playercards &opponentCards = shared->getOpponentCards();
   int numOfPendingMulliganCards=0;
   if( c.getType() == choicetype::card )
   {
      // set pending mulligan card
      for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
      {
         if (c.getTargetCard() == gameCards.province[i])
         {
            gameCards.pending_dynasty_mulligan[i] = true;
         }
         if( gameCards.pending_dynasty_mulligan[i] )
         {
            numOfPendingMulliganCards++;
         }
      }
   }
   // process a pass on mulligan or a full set of cards mulliganed
   if( c.getType() == choicetype::pass || numOfPendingMulliganCards == NUM_DYNASTY_PROVINCES)
   {
      bool noMulligans = discardDynastyMulligans();

      if(!noMulligans)
      {
         replaceDynastyMulligans();
      }

      if( shared->state.currentAction != shared->state.currentTurn )
      {
         drawConflictCards(shared->getOpponentPlayer()->getName(), opponentCards);
         drawConflictCards(shared->getCurrentPlayer()->getName(), gameCards);
         shared->state.currentSubPhase = subphase::conflict_mulligan;
      }
      shared->swapCurrentActionPlayer();
   }
}

void pregameEngine::drawConflictCards(std::string playerName, playercards &gameCards)
{
   auto cd = gameCards.conflict_drawdeck.begin();
   std::cout << playerName << " draws 4 conflict cards" << std::endl;
   for(int i=0;i < STARTING_NUM_CONFLICT_CARDS;i++)
   {
      gameCards.conflict_hand.push_back(*cd);
      card &conflictCard = shared->cardList.at(*cd);
      std::cout << " " << conflictCard.getName() <<  std::endl;
      cd = gameCards.conflict_drawdeck.erase(cd);
   }
}

void pregameEngine::doConflictMulligan(choice c)
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   playercards &opponentCards = shared->getOpponentCards();
   if( c.getType() == choicetype::card )
   {
      bool found = false;
      for(auto cc = gameCards.conflict_hand.begin();(cc !=  gameCards.conflict_hand.end()) && !found; ++cc )
      {
         if(*cc == c.getTargetCard())
         {
            gameCards.pending_conflict_mulligan.push_back(*cc);
            cc = gameCards.conflict_hand.erase(cc);
            found = true;
         }
      }
      if(!found)
      {
         throw std::runtime_error("Couldn't find the mulligan card");
      }
   }
   // process a pass on mulligan or a full set of cards mulliganed
   if( c.getType() == choicetype::pass || gameCards.pending_conflict_mulligan.size() == STARTING_NUM_CONFLICT_CARDS)
   {
      std::cout << shared->getCurrentPlayer()->getName() << " mulligans" <<  std::endl;
      int numOfMulligans=gameCards.pending_conflict_mulligan.size();
      for(auto cc = gameCards.pending_conflict_mulligan.begin(); cc != gameCards.pending_conflict_mulligan.end();)
      {
         card &conflictCard = shared->cardList.at(*cc);
         std::cout << " " << conflictCard.getName() << std::endl;
         gameCards.conflict_drawdeck.push_back(*cc);
         cc = gameCards.conflict_hand.erase(cc);
      }
      if (numOfMulligans == 0)
      {
         std::cout << " nothing" << std::endl;
      }
      else
      {
         std::cout << shared->getCurrentPlayer()->getName() << " draws " << numOfMulligans << " cards" <<  std::endl;
         auto cc = gameCards.conflict_drawdeck.begin();
         for(int i=0;i<numOfMulligans;i++)
         {
            card &conflictCard = shared->cardList.at(*cc);
            std::cout << " " << conflictCard.getName() << std::endl;
            gameCards.conflict_hand.push_back(*cc);
            cc = gameCards.conflict_drawdeck.erase(cc);
         }
      }

      if(shared->state.currentAction != shared->state.currentTurn)
      {
         gainHonor(shared->getOpponentPlayer()->getName(), opponentCards);
         gainHonor(shared->getCurrentPlayer()->getName(), gameCards);

         // add unclaimed rings
         shared->state.unclaimed_rings.clear();
         shared->state.unclaimed_rings.push_back(ring::air);
         shared->state.unclaimed_rings.push_back(ring::fire);
         shared->state.unclaimed_rings.push_back(ring::earth);
         shared->state.unclaimed_rings.push_back(ring::water);
         shared->state.unclaimed_rings.push_back(ring::_void);

         shared->state.currentPhase = phase::dynasty;
         shared->state.currentSubPhase = subphase::dynasty_setup;
      }
      shared->swapCurrentActionPlayer();
   }
}

void pregameEngine::gainHonor(std::string playerName, playercards &gameCards)
{
   card &stronghold = shared->cardList.at(gameCards.stronghold);
   int honorValue = stronghold.getStrongholdHonor();
   std::cout << playerName << " receives " << honorValue << " honor from "
      << stronghold.getName() <<std::endl;
   gameCards.honorTokens = honorValue;
   gameCards.fate = 0;
}

void pregameEngine::doAction(choice c)
{
}
