#include "cardareamanager.h"
#include "carddatamanager.h"
#include "state/cardarea.h"

using namespace l5r;

CardAreaManager::CardAreaManager(cardarea *cardArea, std::string name, std::shared_ptr<cardDataManager> cardMgr) : cardArea(cardArea), name(name), cardMgr(cardMgr)
{
}

CardAreaManager::~CardAreaManager()
{
}

void CardAreaManager::setupCards(decklist deck, std::vector<cards> &cardIds)
{
   // shouldn't be cards here but clear just in case
   cardArea->dynastyDeck.clear();

   for(auto c: deck.getList())
   {
      // add to global table for unique id
      cardIds.push_back(c);

      switch(cardMgr->getCardType(c))
      {
         case cardtype::dynasty:
            cardArea->dynastyDeck.push_back(cardIds.size() - 1);
            break;
         case cardtype::province:
            provinceStack ps;
            ps.provinceCard = cardIds.size() -1;
            ps.dynastyCard = -1;// no dynasty card yet
            ps.facedownDynasty = false;
            ps.provinceStatus = provinceCardStatus::unrevealed;

            cardArea->provinceArea.push_back(ps);
            break;
         case cardtype::stronghold:
            cardIds.push_back(c);
            cardArea->stronghold = cardIds.size() - 1;
            break;
         case cardtype::conflict:
            cardArea->conflictDeck.push_back(cardIds.size() - 1);
            break;
         default:
            break;
      }
   }
}

