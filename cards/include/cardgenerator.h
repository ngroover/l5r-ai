#ifndef _CARDGENERATOR_H_
#define _CARDGENERATOR_H_

#include <list>
#include <map>
#include <carddata.h>
#include <cards.h>
#include <decklist.h>
#include "carddatagenerator.h"

namespace l5r
{
   class cardgenerator
   {
      public:
         cardgenerator();
         ~cardgenerator();

         CardDataSharedPtr generateCard(cards c);

         std::map<cards,CardDataSharedPtr> generateCards(decklist deck);

      private:
         std::string getStringId(cards c);
         CardDataGenerator generator;
   };
};

#endif //_CARDGENERATOR_H_
