#include "dynastycardmanager.h"
#include <iostream>

using namespace l5r;


dynastyCardManager::dynastyCardManager(std::shared_ptr<gamestate> state,std::shared_ptr<cardDataManager> cardMgr, std::shared_ptr<agentManager> agentMgr):state(state), cardMgr(cardMgr), agentMgr(agentMgr)
{
}

dynastyCardManager::~dynastyCardManager()
{
}


void dynastyCardManager::createDeck(decklist deck, int playerNum)
{
   // shouldn't be cards here but clear just in case
   state->getPlayerState(playerNum).dynastyDeck.clear();

   for(auto c: deck.getList())
   {
      if(cardMgr->getCardType(c) == cardtype::dynasty)
      {
         // add to global table for unique id
         state->cardIds.push_back(c);
         
         // add card to deck
         state->getPlayerState(playerNum).dynastyDeck.push_back(state->cardIds.size() - 1);
      }
   }
}

void dynastyCardManager::fillProvinces(playerstate &pState, std::string playerName)
{
   auto dynastyDeck = pState.dynastyDeck.begin();
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->dynastyCard == -1)
      {
         prov->dynastyCard = *dynastyDeck;
         prov->facedownDynasty = true;
         dynastyDeck = pState.dynastyDeck.erase(dynastyDeck);
         std::cout << playerName
            << " placed " << cardMgr->getCardName(prov->dynastyCard)
            << " on top of " << cardMgr->getCardName(prov->provinceCard)
            << std::endl;
      }
   }
}

void dynastyCardManager::chooseMulliganCard(int cardChoice)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->dynastyCard == cardChoice)
      {
         // set no card on top of province
         prov->dynastyCard = -1;
         pState.pendingMulligan.push_back(cardChoice);
      }
   }
}

void dynastyCardManager::performMulligan()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::cout << agentMgr->getPlayerName(relativePlayer::myself)
      << " mulligans:" << std::endl;
   if( pState.pendingMulligan.size() == 0)
   {
      std::cout << "Nothing" << std::endl;
   }
   else
   {
      for(auto mul: pState.pendingMulligan)
      {
         pState.dynastyDeck.push_back(mul);
         std::cout << " " << cardMgr->getCardName(mul) << std::endl;
      }
   }
   pState.pendingMulligan.clear();
}

std::list<choice> dynastyCardManager::getProvinceDynastyChoices(dynastyCardStatus dcs)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list;
   for(auto prov:pState.provinceArea)
   {
      if( ((dcs == dynastyCardStatus::facedown && prov.facedownDynasty) ||
         (dcs == dynastyCardStatus::faceup && !prov.facedownDynasty) ||
         (dcs == dynastyCardStatus::either))
         && prov.dynastyCard != -1)
      {
         choice c(cardMgr->getCardName(prov.dynastyCard), choicetype::card);
         c.setNumber(prov.dynastyCard);
         list.push_back(c);
      }
   }
   return list;
}

void dynastyCardManager::flipAllDynastyFaceup(playerstate &pState, std::string playerName)
{
   auto dynastyDeck = pState.dynastyDeck.begin();
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->facedownDynasty)
      {
         prov->facedownDynasty = false;
         std::cout << playerName
            << " flipped " << cardMgr->getCardName(prov->dynastyCard)
            << " faceup " << std::endl;
      }
   }
}

std::list<choice> dynastyCardManager::getProvinceDynastyChoicesWithFate(dynastyCardStatus dcs, int fateCost)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list;
   for(auto prov:pState.provinceArea)
   {
      if(prov.dynastyCard != -1)
      {
         int cardCost = cardMgr->getFateCost(prov.dynastyCard);
         if( ((dcs == dynastyCardStatus::facedown && prov.facedownDynasty) ||
            (dcs == dynastyCardStatus::faceup && !prov.facedownDynasty) ||
            (dcs == dynastyCardStatus::either))
            && cardCost <= fateCost)
         {
            choice c(cardMgr->getCardName(prov.dynastyCard), choicetype::card);
            c.setNumber(prov.dynastyCard);
            list.push_back(c);
         }
      }
   }
   return list;
}

void dynastyCardManager::chooseCharacterToPlay(playerstate &pState, int index)
{
   pState.pendingFateCard = index;
}

int dynastyCardManager::getPendingFateCard(playerstate &pState)
{
   return pState.pendingFateCard;
}

void dynastyCardManager::playCharacter(playerstate &pState, std::string playerName)
{
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->dynastyCard == pState.pendingFateCard)
      {
         std::cout << "Playing " << 
            cardMgr->getCardName(prov->dynastyCard) << std::endl;
         // set no card on top of province
         prov->dynastyCard = -1;
         pState.atHome.push_back(pState.pendingFateCard);
      }
   }
}

void dynastyCardManager::removeCharacterFromHome(playerstate &pState, int cardChoice)
{
   for(auto ch=pState.atHome.begin();ch!=pState.atHome.end();ch++)
   {
      if(*ch == cardChoice)
      {
         pState.atHome.erase(ch);
         ch = pState.atHome.end();
      }
   }
}

std::list<choice> dynastyCardManager::getAttackerChoices(playerstate &pState)
{
   std::list<choice> list;
   for(auto ch=pState.atHome.begin();ch!=pState.atHome.end();ch++)
   {
      // TODO: check dashed types can't be mixed into conflict
      choice c(cardMgr->getCardName(*ch), choicetype::card);
      c.setNumber(*ch);
      list.push_back(c);
   }
   return list;
}

std::list<choice> dynastyCardManager::getDefenderChoices(playerstate &pState)
{
   std::list<choice> list;
   for(auto ch=pState.atHome.begin();ch!=pState.atHome.end();ch++)
   {
      // TODO: check dashed types can't be mixed into conflict
      choice c(cardMgr->getCardName(*ch), choicetype::card);
      c.setNumber(*ch);
      list.push_back(c);
   }
   return list;
}

int dynastyCardManager::conflictTotal(playerstate &pState)
{
   return 0;
}
