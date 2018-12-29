#include "provincecardmanager.h"
#include <iostream>

using namespace l5r;


provinceCardManager::provinceCardManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr, std::shared_ptr<agentManager> agentMgr):state(state), cardMgr(cardMgr), agentMgr(agentMgr)
{
}

provinceCardManager::~provinceCardManager()
{
}

void provinceCardManager::createDeck(decklist deck, int playerNum)
{
   // shouldn't be cards here but clear just in case
   state->getPlayerState(playerNum).provinceArea.clear();

   for(auto c: deck.getList())
   {
      if(cardMgr->getCardType(c) == cardtype::province)
      {
         // add to global table for unique id
         state->cardIds.push_back(c);
         
         // add card to deck
         provinceStack ps;
         ps.provinceCard = state->cardIds.size() -1;
         ps.dynastyCard = -1;// no dynasty card yet
         ps.facedownDynasty = false;
         ps.isBroken = false;
         ps.provinceStatus = provinceCardStatus::unrevealed;

         state->getPlayerState(playerNum).provinceArea.push_back(ps);
      }
      if(cardMgr->getCardType(c) == cardtype::stronghold)
      {
         state->cardIds.push_back(c);
         int id = state->cardIds.size() - 1;
         state->getPlayerState(playerNum).stronghold = id;
      }
   }
}

void provinceCardManager::chooseStronghold(int provinceChoice)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->provinceCard == provinceChoice)
      {
         pState.provinceArea.erase(prov);
         pState.strongholdProvince = provinceChoice;
         prov = pState.provinceArea.end();
         std::cout << agentMgr->getPlayerName(relativePlayer::myself)
            << " chose " << cardMgr->getCardName(provinceChoice) 
            << " for a stronghold" << std::endl;
      }
   }
}

int provinceCardManager::getStartingHonor(int playerNum)
{
   playerstate &pState = state->getPlayerState(playerNum);
   return cardMgr->getStrongholdHonor(pState.stronghold);
}

std::list<choice> provinceCardManager::getStrongholdChoices()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list;
   for(auto prov:pState.provinceArea)
   {
      choice c(cardMgr->getCardName(prov.provinceCard), choicetype::card);
      c.setNumber(prov.provinceCard);
      list.push_back(c);
   }
   return list;
}

std::list<choice> provinceCardManager::getProvinceChoices(playerstate &pState)
{
   std::list<choice> list;
   for(auto pc:pState.provinceArea)
   {
      if(pc.provinceStatus != provinceCardStatus::broken)
      {
         choice c(cardMgr->getCardName(pc.provinceCard), choicetype::card);
         c.setNumber(pc.provinceCard);
         list.push_back(c);
      }
   }
   return list;
}

void provinceCardManager::breakProvince(playerstate &pState, int cardIndex)
{
   for(auto p:pState.provinceArea)
   {
      if(p.provinceCard == cardIndex)
      {
         std::cout << cardMgr->getCardName(cardIndex) << " breaks!" << std::endl;
         p.isBroken = true;
      }
   }
}

