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

void CardAreaManager::setupCards(Decklist deck)
{
   // shouldn't be cards here but clear just in case
   cardArea->dynastyDeck.clear();
   cardArea->pendingFateCard = nullptr;

   for(auto cardStr : deck.getList())
   {
      CardSharedPtr csp = cardMgr->getCard(cardStr);

      switch(csp->data->side)
      {
         case deckside::dynasty:
            cardArea->dynastyDeck.push_back(csp);
            break;
         case deckside::province:
            if(csp->data->type == cardtype::stronghold)
            {
               cardArea->stronghold = csp;
            }
            else
            {
               CardSharedPtr prov = csp;
               csp->provinceStatus = provinceCardStatus::unrevealed;
               csp->facedownDynasty = false;
               cardArea->provinceArea.push_back(csp);
               cardArea->dynastyArea.push_back(nullptr);
            }
            break;
         case deckside::conflict:
            cardArea->conflictDeck.push_back(csp);
            break;
         default:
            break;
      }
   }
}

