#ifndef _CARDGENERATOR_H_
#define _CARDGENERATOR_H_

#include <list>
#include <map>
#include <card.h>
#include <cards.h>
#include <decklist.h>

namespace l5r
{
   class cardgenerator
   {
      public:
         cardgenerator();
         ~cardgenerator();

         card generateCard(cards c);

         std::map<cards,card> generateCards(decklist deck);
   };
};

#endif //_CARDGENERATOR_H_
