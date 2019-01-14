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
   if(dynastyDeck == pState.dynastyDeck.end())
   {
      std::cout << "Deck is empty!" << std::endl;
      pState.dynastyDeck = pState.dynastyDiscard;
      pState.dynastyDiscard.clear();
      dynastyDeck = pState.dynastyDeck.begin();
      std::cout << " top card is " << cardMgr->getCardName(*dynastyDeck) << std::endl;
      
   }
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->dynastyCard == -1)
      {
         prov->dynastyCard = *dynastyDeck;
         prov->facedownDynasty = true;
         dynastyDeck = pState.dynastyDeck.erase(dynastyDeck);
         if(dynastyDeck == pState.dynastyDeck.end())
         {
            std::cout << "Deck is empty!" << std::endl;
            pState.dynastyDeck = pState.dynastyDiscard;
            pState.dynastyDiscard.clear();
            dynastyDeck = pState.dynastyDeck.begin();
            std::cout << " top card is " << cardMgr->getCardName(*dynastyDeck) << std::endl;
            
         }
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

std::list<choice> dynastyCardManager::getProvinceDynastyChoicesWithFateCost(dynastyCardStatus dcs, int fateCost)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list;
   for(auto prov:pState.provinceArea)
   {
      if(prov.dynastyCard != -1 && cardMgr->getDynastyCardType(prov.dynastyCard) == dynastycardtype::character)
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

std::list<choice> dynastyCardManager::getCharactersWithNoFate()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   std::list<choice> list;
   for(auto ch:pState.atHome)
   {
      if(ch.fateAttached == 0)
      {
         choice c(cardMgr->getCardName(ch.characterCard), choicetype::card);
         c.setNumber(ch.characterCard);
         list.push_back(c);
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

int dynastyCardManager::getPendingCharCost(playerstate &pState)
{
   return cardMgr->getFateCost(pState.pendingFateCard);
}

void dynastyCardManager::playCharacter(playerstate &pState, std::string playerName, int extraFate)
{
   for(auto prov=pState.provinceArea.begin();prov!=pState.provinceArea.end();++prov)
   {
      if(prov->dynastyCard == pState.pendingFateCard)
      {
         std::cout << "Playing " << 
            cardMgr->getCardName(prov->dynastyCard) << std::endl;
         // set no card on top of province
         prov->dynastyCard = -1;
         inplaycharacter ipc;
         ipc.characterCard = pState.pendingFateCard;
         ipc.bowed = false;
         ipc.fateAttached = extraFate;
         pState.atHome.push_back(ipc);
      }
   }
}

inplaycharacter dynastyCardManager::removeCharacterFromHome(playerstate &pState, int cardChoice)
{
   for(auto ch=pState.atHome.begin();ch!=pState.atHome.end();ch++)
   {
      if(ch->characterCard == cardChoice)
      {
         pState.atHome.erase(ch);
         return *ch;
         ch = pState.atHome.end();
      }
   }
   throw std::runtime_error("Character not found");
}

std::list<choice> dynastyCardManager::getAttackerChoices(playerstate &pState)
{
   std::list<choice> list;
   for(auto ch=pState.atHome.begin();ch!=pState.atHome.end();ch++)
   {
      // TODO: check dashed types can't be mixed into conflict
      if(!ch->bowed)
      {
         choice c(cardMgr->getCardName(ch->characterCard), choicetype::card);
         c.setNumber(ch->characterCard);
         list.push_back(c);
      }
   }
   return list;
}

std::list<choice> dynastyCardManager::getDefenderChoices(playerstate &pState)
{
   std::list<choice> list;
   for(auto ch=pState.atHome.begin();ch!=pState.atHome.end();ch++)
   {
      // TODO: check dashed types can't be mixed into conflict
      if(!ch->bowed)
      {
         choice c(cardMgr->getCardName(ch->characterCard), choicetype::card);
         c.setNumber(ch->characterCard);
         list.push_back(c);
      }
   }
   return list;
}

int dynastyCardManager::conflictTotal(playerstate &pState)
{
   return 0;
}

void dynastyCardManager::sendCharactersHome(std::list<inplaycharacter> charlist, playerstate &pState)
{
   std::cout << "Sent home" << std::endl;
   for(auto c: charlist)
   {
      std::cout << " " << cardMgr->getCardName(c.characterCard) << std::endl;
      pState.atHome.push_back(c);
   }
}

int dynastyCardManager::countFavorGlory(playerstate &pState)
{
   int gloryCount=0;
   for(auto c: pState.atHome)
   {
      if(!c.bowed)
      {
         gloryCount += cardMgr->getGlory(c.characterCard);
      }
   }
   return gloryCount;
}

void dynastyCardManager::discardCharacter(int cardIndex)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   for(auto ptr=pState.atHome.begin();
      ptr!=pState.atHome.end();
      ptr++)
   {
      if(ptr->characterCard == cardIndex)
      {
         pState.dynastyDiscard.push_back(ptr->characterCard);
         std::cout << "Discarding " << cardMgr->getCardName(cardIndex) << std::endl;
         pState.atHome.erase(ptr);
         ptr = pState.atHome.end();
      }
   }
}

void dynastyCardManager::removeFateFromCharacters()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
   for(auto &ch:pState.atHome)
   {
      if(ch.fateAttached > 0)
      {
         ch.fateAttached--;
         std::cout << "Removed 1 fate from " << cardMgr->getCardName(ch.characterCard) << std::endl;
      }
   }
   for(auto &ch:oppState.atHome)
   {
      if(ch.fateAttached > 0)
      {
         ch.fateAttached--;
         std::cout << "Removed 1 fate from " << cardMgr->getCardName(ch.characterCard) << std::endl;
      }
   }
}

void dynastyCardManager::discardProvinceCard(int cardIndex)
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   for(auto ptr=pState.provinceArea.begin();
      ptr!=pState.provinceArea.end();
      ptr++)
   {
      if(ptr->dynastyCard == cardIndex)
      {
         pState.dynastyDiscard.push_back(ptr->dynastyCard);
         ptr->dynastyCard = -1;
         std::cout << "Discarding " << cardMgr->getCardName(cardIndex) << std::endl;
      }
   }
}
void dynastyCardManager::readyAllCharacters()
{
   playerstate &pState = state->getPlayerState(relativePlayer::myself);
   playerstate &oppState = state->getPlayerState(relativePlayer::opponent);
   for(auto &ch:pState.atHome)
   {
      ch.bowed = false;
      std::cout << cardMgr->getCardName(ch.characterCard) << " readied" << std::endl;
   }
   for(auto &ch:oppState.atHome)
   {
      ch.bowed = false;
      std::cout << cardMgr->getCardName(ch.characterCard) << " readied" << std::endl;
   }
}
