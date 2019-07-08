#ifndef _DECKLIST_MANAGER_H_
#define _DECKLIST_MANAGER_H_

#include <string>
#include <map>
#include "decklist.h"

namespace l5r
{
   class DecklistManager
   {
      public:
         DecklistManager(std::string pathToDeckData);
         ~DecklistManager();

         DecklistSharedPtr findDeck(std::string deckName);
         
      private:
         std::map< std::string, DecklistSharedPtr> deckMap;
   };
};

#endif //_DECKLIST_MANAGER_H_
