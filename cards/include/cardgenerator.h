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

         CardDataSharedPtr generateCard(std::string c);

         std::map<cards,CardDataSharedPtr> generateCards(Decklist deck);

      private:
         cards fromStringId(std::string c);
         CardDataGenerator generator;
   };
};

#endif //_CARDGENERATOR_H_
