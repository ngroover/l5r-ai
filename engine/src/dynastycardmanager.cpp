#include "dynastycardmanager.h"
#include <iostream>
#include "state/cardarea.h"
#include "tokenmanager.h"

using namespace l5r;


dynastyCardManager::dynastyCardManager(std::shared_ptr<gamestate> state,std::shared_ptr<cardDataManager> cardMgr):state(state), cardMgr(cardMgr)
{
}

dynastyCardManager::~dynastyCardManager()
{
}


void dynastyCardManager::fillProvinces(cardarea *cards, tokenManager *tokens, std::string playerName)
{
   auto dynastyDeck = cards->dynastyDeck.begin();
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov)
   {
      if(prov->dynastyCard == -1)
      {
         if(dynastyDeck == cards->dynastyDeck.end())
         {
            std::cout << "Deck is empty!" << std::endl;
            cards->dynastyDeck = cards->dynastyDiscard;
            cards->dynastyDiscard.clear();
            tokens->loseHonor(5);
            if(tokens->dishonorLoss())
            {
               return;
            }
            dynastyDeck = cards->dynastyDeck.begin();
            std::cout << " top card is " << cardMgr->getCardName(*dynastyDeck) << std::endl;
            
         }
         prov->dynastyCard = *dynastyDeck;
         prov->facedownDynasty = true;
         dynastyDeck = cards->dynastyDeck.erase(dynastyDeck);
         std::cout << playerName
            << " placed " << cardMgr->getCardName(prov->dynastyCard)
            << " on top of " << cardMgr->getCardName(prov->provinceCard)
            << std::endl;
      }
   }
}

void dynastyCardManager::flipAllDynastyFaceup(cardarea *cards, std::string playerName)
{
   auto dynastyDeck = cards->dynastyDeck.begin();
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov)
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

std::list<choice> dynastyCardManager::getProvinceDynastyChoices(cardarea *cards, dynastyCardStatus dcs)
{
   std::list<choice> list;
   for(auto prov:cards->provinceArea)
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

std::list<choice> dynastyCardManager::getProvinceDynastyChoicesWithFateCost(cardarea *cards, dynastyCardStatus dcs, int fateCost)
{
   std::list<choice> list;
   for(auto prov:cards->provinceArea)
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

std::list<choice> dynastyCardManager::getCharactersWithNoFate(cardarea *cards)
{
   std::list<choice> list;
   for(auto ch:cards->atHome)
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

void dynastyCardManager::chooseCharacterToPlay(cardarea *cards, int index)
{
   cards->pendingFateCard = index;
}

int dynastyCardManager::getPendingFateCard(cardarea *cards)
{
   return cards->pendingFateCard;
}

int dynastyCardManager::getPendingCharCost(cardarea *cards)
{
   return cardMgr->getFateCost(cards->pendingFateCard);
}

void dynastyCardManager::playCharacter(cardarea *cards, std::string playerName, int extraFate)
{
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov)
   {
      if(prov->dynastyCard == cards->pendingFateCard)
      {
         std::cout << "Playing " << 
            cardMgr->getCardName(prov->dynastyCard) << std::endl;
         // set no card on top of province
         prov->dynastyCard = -1;
         inplaycharacter ipc;
         ipc.characterCard = cards->pendingFateCard;
         ipc.bowed = false;
         ipc.fateAttached = extraFate;
         cards->atHome.push_back(ipc);
      }
   }
}


std::list<choice> dynastyCardManager::getAttackerChoices(cardarea *cards)
{
//moved
}

std::list<choice> dynastyCardManager::getDefenderChoices(cardarea *cards)
{
}

int dynastyCardManager::conflictTotal(playerstate &pState)
{
   return 0;
}

void dynastyCardManager::sendCharactersHome(std::list<inplaycharacter> charlist, cardarea *cards)
{
   std::cout << "Sent home" << std::endl;
   for(auto c: charlist)
   {
      std::cout << " " << cardMgr->getCardName(c.characterCard) << std::endl;
      cards->atHome.push_back(c);
   }
}


void dynastyCardManager::discardCharacter(cardarea *cards, int cardIndex)
{
   for(auto ptr=cards->atHome.begin();
      ptr!=cards->atHome.end();
      ptr++)
   {
      if(ptr->characterCard == cardIndex)
      {
         cards->dynastyDiscard.push_back(ptr->characterCard);
         std::cout << "Discarding " << cardMgr->getCardName(cardIndex) << std::endl;
         cards->atHome.erase(ptr);
         ptr = cards->atHome.end();
      }
   }
}

void dynastyCardManager::removeFateFromCharacters(cardarea *cards)
{
   for(auto &ch:cards->atHome)
   {
      if(ch.fateAttached > 0)
      {
         ch.fateAttached--;
         std::cout << "Removed 1 fate from " << cardMgr->getCardName(ch.characterCard) << std::endl;
      }
   }
}

void dynastyCardManager::discardProvinceCard(cardarea *cards, int cardIndex)
{
   for(auto ptr=cards->provinceArea.begin();
      ptr!=cards->provinceArea.end();
      ptr++)
   {
      if(ptr->dynastyCard == cardIndex)
      {
         cards->dynastyDiscard.push_back(ptr->dynastyCard);
         ptr->dynastyCard = -1;
         std::cout << "Discarding " << cardMgr->getCardName(cardIndex) << std::endl;
      }
   }
}
void dynastyCardManager::readyAllCharacters(cardarea *cards)
{
   for(auto &ch:cards->atHome)
   {
      ch.bowed = false;
      std::cout << cardMgr->getCardName(ch.characterCard) << " readied" << std::endl;
   }
}
