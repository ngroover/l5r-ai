#include "pregameengine.h"
#include <algorithm>
#include <iostream>

using namespace l5r;


pregameEngine::pregameEngine(std::shared_ptr<engineShared> es) : shared(es)
{
}

pregameEngine::~pregameEngine()
{
}

decision pregameEngine::getDecision()
{
   // currentPhase should be pregame
   playercards &gameCards=shared->getCurrentPlayerCards();
   if(shared->state.currentSubPhase == subphase::stronghold_selection)
   {
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
   else if(shared->state.currentSubPhase == subphase::dynasty_mulligan)
   {
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
   else
   {
      throw "Invalid substate";
   }
}

void pregameEngine::doAction(choice c)
{
   // currentPhase should be pregame
   playercards &gameCards=shared->getCurrentPlayerCards();
   playercards &opponentCards=shared->getOpponentCards();
   if(shared->state.currentSubPhase == subphase::stronghold_selection)
   {
      if( c.getType() == choicetype::card )
      {
         gameCards.strongholdProvince = c.getTargetCard();
         card &strongholdCard = shared->cardList.at(c.getTargetCard());
         std::cout << shared->getCurrentPlayer()->getName() << " chose " << strongholdCard.getName() << " as stronghold" << std::endl;
         // print province row
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

         // switch action
         if (shared->state.currentAction == shared->state.currentTurn)
         {
            if(shared->state.currentAction == player::player1)
            {
               shared->state.currentAction = player::player2;
            }
            else
            {
               shared->state.currentAction = player::player1;
            }
         }
         // travel to the next state ( dyntasy mulligan )
         else
         {
            auto dd = opponentCards.dynasty_drawdeck.begin();
            for(int i=0;i<NUM_DYNASTY_PROVINCES;i++)
            {
               opponentCards.province_dynasty[i] = *dd;
               card &dynastyCard = shared->cardList.at(*dd);
               card &provinceCard = shared->cardList.at(opponentCards.province[i]);
               std::cout << "Placing " << 
                  dynastyCard.getName() << " on " <<
                  provinceCard.getName() << std::endl;
               // remove card from top of drawdeck and increment iterator to the next
               dd = opponentCards.dynasty_drawdeck.erase(dd);
            }
            shared->state.currentAction = shared->state.currentTurn;
            shared->state.currentSubPhase = subphase::dynasty_mulligan;
         }
      }
      else
      {
         throw "Not a card choice!";
      }
   }
   else if(shared->state.currentSubPhase == subphase::dynasty_mulligan)
   {
      if( c.getType() == choicetype::card )
      {
         for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
         {
            if (c.getTargetCard() == gameCards.province[i])
            {
               gameCards.pending_dynasty_mulligan[i] = true;
            }
         }
      }
      else if( c.getType() == choicetype::pass )
      {
         std::cout << shared->getCurrentPlayer()->getName() << " mulligans" <<  std::endl;
         bool noMulligans=true;
         for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
         {
            if(gameCards.pending_dynasty_mulligan[i])
            {
               noMulligans = false; 
               card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
               card &provCard = shared->cardList.at(gameCards.province[i]);
               std::cout << " " << dynastyCard.getName() << " on " << provCard.getName() << std::endl;
            }
         }

         if(noMulligans)
         {
            std::cout << " nothing" << std::endl;
         }
         auto dd = gameCards.dynasty_drawdeck.begin();

         for (int i=0;i<NUM_DYNASTY_PROVINCES;i++)
         {
            if(gameCards.pending_dynasty_mulligan[i])
            {
               noMulligans = false; 
               card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
               card &provCard = shared->cardList.at(gameCards.province[i]);
               card &nextDynastyCard = shared->cardList.at(*dd);
               std::cout << "Discarding " << dynastyCard.getName() << " on " << provCard.getName() << 
                    " and replacing with " << nextDynastyCard.getName() << " from deck " << std::endl;
               dd = gameCards.dynasty_drawdeck.erase(dd);
            }
         }

         if( shared->state.currentAction == shared->state.currentTurn )
         {
            // TODO: flip all cards before mulliganing
            // doesn't really matter I guess since theres no hidden info
            auto dd = opponentCards.dynasty_drawdeck.begin();
            for(int i=0;i<NUM_DYNASTY_PROVINCES;i++)
            {
               opponentCards.province_dynasty[i] = *dd;
               card &dynastyCard = shared->cardList.at(*dd);
               card &provinceCard = shared->cardList.at(opponentCards.province[i]);
               std::cout << "Placing " << 
                  dynastyCard.getName() << " from deck on " <<
                  provinceCard.getName() << std::endl;
               // remove card from top of drawdeck and increment iterator to the next
               dd = opponentCards.dynasty_drawdeck.erase(dd);
            }
            if(shared->state.currentAction == player::player1 )
            {
               shared->state.currentAction = player::player2;
            }
            else
            {
               shared->state.currentAction = player::player1;
            }
         }
         else
         {
            //shared->state.currentPhase = phase::gameover;
            /*shared->state.currentSubPhase = subphase::conflict_mulligan;
            if(shared->state.currentAction == player::player1 )
            {
               shared->state.currentAction = player::player2;
            }
            else
            {
               shared->state.currentAction = player::player1;
            }*/
         }
      }
   }
}
