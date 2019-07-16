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
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end();++prov,++dynastyArea)
   {
      if(*dynastyArea == nullptr)
      {
         if(dynastyDeck == cards->dynastyDeck.end())
         {
            std::cout << "Deck is empty!" << std::endl;
            cards->dynastyDeck = cards->dynastyDiscard;
            cards->dynastyDiscard.clear();
            tokens->loseHonor(5);
            dynastyDeck = cards->dynastyDeck.begin();
            std::cout << " top card is " << (*dynastyDeck)->data->name << std::endl;
            
         }
         *dynastyArea = *dynastyDeck;
         (*prov)->facedownDynasty = true;
         dynastyDeck = cards->dynastyDeck.erase(dynastyDeck);
         std::cout << playerName
            << " placed " << (*dynastyArea)->data->name 
            << " on top of " << (*prov)->data->name
            << std::endl;
      }
   }
}

void dynastyCardManager::flipAllDynastyFaceup(cardarea *cards, std::string playerName)
{
   auto dynastyDeck = cards->dynastyDeck.begin();
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end() && dynastyArea!=cards->dynastyArea.end();++prov,++dynastyArea)
   {
      if((*prov)->facedownDynasty)
      {
         (*prov)->facedownDynasty = false;
         std::cout << playerName
            << " flipped " << (*dynastyArea)->data->name
            << " faceup " << std::endl;
      }
   }
}

std::list<choice> dynastyCardManager::getProvinceDynastyChoices(cardarea *cards, dynastyCardStatus dcs)
{
   std::list<choice> list;
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov:cards->provinceArea)
   {
      if( ((dcs == dynastyCardStatus::facedown && prov->facedownDynasty) ||
         (dcs == dynastyCardStatus::faceup && !prov->facedownDynasty) ||
         (dcs == dynastyCardStatus::either))
         && (*dynastyArea != nullptr))
      {
         choice c( (*dynastyArea)->data->name, choicetype::card);
         c.setCard(*dynastyArea);
         list.push_back(c);
      }
      dynastyArea++;
   }
   return list;
}

std::list<choice> dynastyCardManager::getProvinceDynastyChoicesWithFateCost(cardarea *cards, dynastyCardStatus dcs, int fateCost)
{
   std::list<choice> list;
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov:cards->provinceArea)
   {
      if((*dynastyArea) != nullptr && (*dynastyArea)->data->type == cardtype::character)
      {
         int cardCost = (*dynastyArea)->data->fateCost;
         if( ((dcs == dynastyCardStatus::facedown && prov->facedownDynasty) ||
            (dcs == dynastyCardStatus::faceup && !prov->facedownDynasty) ||
            (dcs == dynastyCardStatus::either))
            && cardCost <= fateCost)
         {
            choice c( (*dynastyArea)->data->name, choicetype::card);
            c.setCard(*dynastyArea);
            list.push_back(c);
         }
      }
      dynastyArea++;
   }
   return list;
}

std::list<choice> dynastyCardManager::getCharactersWithNoFate(cardarea *cards)
{
   std::list<choice> list;
   for(auto ch:cards->atHome)
   {
      if(ch->fateAttached == 0)
      {
         choice c(ch->data->name, choicetype::card);
         c.setCard(ch);
         list.push_back(c);
      }
   }
   return list;
}

void dynastyCardManager::chooseCharacterToPlay(cardarea *cards, CardSharedPtr index)
{
   cards->pendingFateCard = index;
}

CardSharedPtr dynastyCardManager::getPendingFateCard(cardarea *cards)
{
   return cards->pendingFateCard;
}

int dynastyCardManager::getPendingCharCost(cardarea *cards)
{
   return cards->pendingFateCard->data->fateCost;
}

void dynastyCardManager::playCharacter(cardarea *cards, std::string playerName, int extraFate)
{
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto prov=cards->provinceArea.begin();prov!=cards->provinceArea.end() && dynastyArea != cards->dynastyArea.end();++prov,++dynastyArea)
   {
      if(*dynastyArea == cards->pendingFateCard)
      {
         std::cout << "Playing " << 
            (*dynastyArea)->data->name << std::endl;
         // set no card on top of province
         (*dynastyArea) = nullptr;
         cards->pendingFateCard->bowed = false;
         cards->pendingFateCard->fateAttached = extraFate;
         cards->atHome.push_back(cards->pendingFateCard);
      }
   }
   cards->pendingFateCard = nullptr; // reset pending fate card
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

void dynastyCardManager::sendCharactersHome(std::vector<CardSharedPtr> charlist, cardarea *cards)
{
   std::cout << "Sent home" << std::endl;
   for(auto &c: charlist)
   {
      std::cout << " " << c->data->name << std::endl;
      cards->atHome.push_back(c);
   }
}


void dynastyCardManager::discardCharacter(cardarea *cards, CardSharedPtr cardIndex)
{
   for(auto ptr=cards->atHome.begin();
      ptr!=cards->atHome.end();
      ptr++)
   {
      if(*ptr == cardIndex)
      {
         cards->dynastyDiscard.push_back(*ptr);
         std::cout << "Discarding " << (*ptr)->data->name << std::endl;
         cards->atHome.erase(ptr);
         ptr = cards->atHome.end();
      }
   }
}

void dynastyCardManager::removeFateFromCharacters(cardarea *cards)
{
   for(auto &ch:cards->atHome)
   {
      if(ch->fateAttached > 0)
      {
         ch->fateAttached--;
         std::cout << "Removed 1 fate from " << ch->data->name << std::endl;
      }
   }
}

void dynastyCardManager::discardProvinceCard(cardarea *cards, CardSharedPtr cardIndex)
{
   auto dynastyArea = cards->dynastyArea.begin();
   for(auto ptr=cards->provinceArea.begin();
      ptr!=cards->provinceArea.end() && dynastyArea != cards->dynastyArea.end();
      ptr++,++dynastyArea)
   {
      if((*dynastyArea) == cardIndex)
      {
         cards->dynastyDiscard.push_back(*dynastyArea);
         (*dynastyArea) = nullptr;
         std::cout << "Discarding " << cardIndex->data->name << std::endl;
      }
   }
}
void dynastyCardManager::readyAllCharacters(cardarea *cards)
{
   for(auto &ch:cards->atHome)
   {
      ch->bowed = false;
      std::cout << ch->data->name << " readied" << std::endl;
   }
}
