#include "dynastyengine.h"
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace l5r;


dynastyEngine::dynastyEngine(std::shared_ptr<engineShared> es) : shared(es)
{
}

dynastyEngine::~dynastyEngine()
{
}

void dynastyEngine::doAction(choice c)
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::dynasty_setup:  //internal transition phase only
         doDynastySetup();
         break;
      case subphase::province_play:
         doProvincePlay(c);
         break;
      case subphase::additional_fate:
         doAdditionalFate(c);
         break;
      default:
         throw "Invalid substate";
   }
}

decision dynastyEngine::getDecision()
{
   switch(shared->state.currentSubPhase)
   {
      case subphase::province_play:
         return provincePlayDecision();
      case subphase::additional_fate:
         return additionalFateDecision();
      default:
         throw "Invalid substate";
   }
}

void dynastyEngine::doDynastySetup()
{
   playercards &gameCards=shared->getCurrentPlayerCards();
   playercards &opponentCards = shared->getOpponentCards();

   // dynasty phase officially begins here
   flipProvinceCards(shared->getCurrentPlayer()->getName(), gameCards);
   flipProvinceCards(shared->getOpponentPlayer()->getName(), opponentCards);

   gainFate(shared->getCurrentPlayer()->getName(), gameCards);
   gainFate(shared->getOpponentPlayer()->getName(), opponentCards);

   shared->state.currentSubPhase = subphase::province_play;
}

void dynastyEngine::flipProvinceCards(std::string playerName, playercards &gameCards)
{
   std::cout << playerName << " flips over dynasty cards" << std::endl;

   for (int i=0;i < NUM_DYNASTY_PROVINCES;i++)
   {
      gameCards.facedown_provinces[i] = false; 
      card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
      std::cout << dynastyCard.getName() << std::endl;
   }
}

void dynastyEngine::gainFate(std::string playerName, playercards &gameCards)
{
   card &stronghold = shared->cardList.at(gameCards.stronghold);
   int fate = STRONGHOLD_FATE;
   std::cout << playerName << " receives " << fate << " fate from "
      << stronghold.getName() <<std::endl;
   gameCards.fate += fate;
}

decision dynastyEngine::provincePlayDecision()
{
   std::list<choice> choiceList;
   playercards &gameCards=shared->getCurrentPlayerCards();
   for(int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
      card &provinceCard = shared->cardList.at(gameCards.province[i]);
      if( dynastyCard.getFateCost() <= gameCards.fate 
      && !gameCards.facedown_provinces[i] )
      {
         std::string action= "Play "+dynastyCard.getName()+" from "+provinceCard.getName();
         choice c(action, choicetype::province_play);
         c.setTargetCard(gameCards.province[i]);
         choiceList.push_back(c);
      }
   }
   choiceList.push_back(choice("pass", choicetype::pass));
   decision d("Choose an Action", choiceList);
   return d;
}

decision dynastyEngine::additionalFateDecision()
{
   std::list<choice> choiceList;
   playercards &gameCards=shared->getCurrentPlayerCards();
   for(int i=0;i<NUM_DYNASTY_PROVINCES;i++)
   {
      card &provinceCard = shared->cardList.at(gameCards.province[i]);
      if(gameCards.pending_fate_card == gameCards.province[i])
      {
         card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
         int leftOverFate = gameCards.fate - dynastyCard.getFateCost();
         if( leftOverFate < 0)
         {
            throw "Not enough fate to pay for card";
         }
         for(int j=0;j <= leftOverFate; j++)
         {
            std::stringstream ss;
            ss << j;
            std::string numFate;
            ss >> numFate;
            choice c(numFate+" Fate", choicetype::fate);
            c.setNumber(j);
            choiceList.push_back(c);
         }
         // TODO: if 0 fate is only option then dont enter this state
         decision d("Choose fate to place on "+dynastyCard.getName(), choiceList);
         return d;
      }
   }
}

void dynastyEngine::doAdditionalFate(choice c)
{
   if(c.getType() == choicetype::fate)
   {
      playercards &gameCards=shared->getCurrentPlayerCards();
      bool found = false;
      for(int i=0;!found && i<NUM_DYNASTY_PROVINCES;i++)
      {
         card &provinceCard = shared->cardList.at(gameCards.province[i]);
         if(gameCards.pending_fate_card == gameCards.province[i])
         {
            card &dynastyCard = shared->cardList.at(gameCards.province_dynasty[i]);
            card &provinceCard = shared->cardList.at(gameCards.province[i]);
            std::string playerName = shared->getCurrentPlayer()->getName();
            int addedFate = c.getNumber();
            std::cout << playerName << " puts " << dynastyCard.getName() <<
               " into play from " << provinceCard.getName() << " with " <<
                addedFate << " fate " << std::endl;
            gameCards.fate -= dynastyCard.getFateCost() + addedFate;
            std::cout << playerName << " now has " << gameCards.fate
               << " fate left" << std::endl;

            gameCards.at_home_characters.push_back(gameCards.province_dynasty[i]);
            auto topDynastyCard = gameCards.dynasty_drawdeck.begin();
            gameCards.province_dynasty[i] = *topDynastyCard;
            card &newdynastyCard = shared->cardList.at(*topDynastyCard);
            std::cout << playerName << " places " << newdynastyCard.getName()
               << " facedown onto " << provinceCard.getName() << std::endl;
            gameCards.dynasty_drawdeck.erase(topDynastyCard);
            gameCards.facedown_provinces[i] = true;

            shared->swapCurrentActionPlayer();
            shared->state.currentSubPhase = subphase::province_play;
            found = true;
         }
      }
   }
   else
   {
      throw "Must be fate choice";
   }
}

void dynastyEngine::doProvincePlay(choice c)
{
   if (c.getType() == choicetype::province_play )
   {
      playercards &gameCards=shared->getCurrentPlayerCards();
      bool found = false;
      for(int i=0;!found && i<NUM_DYNASTY_PROVINCES;i++)
      {
         card &provinceCard = shared->cardList.at(gameCards.province[i]);
         if(c.getTargetCard() == gameCards.province[i])
         {
            gameCards.pending_fate_card = c.getTargetCard();
            found = true;
         }
      }
      shared->state.currentSubPhase = subphase::additional_fate;
   }
   else if (c.getType() == choicetype::pass)
   {
      shared->state.currentPhase = phase::gameover;
   }
}
