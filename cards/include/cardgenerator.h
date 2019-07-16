#ifndef _CARDGENERATOR_H_
#define _CARDGENERATOR_H_

#include <list>
#include <map>
#include <carddata.h>
#include <decklist.h>
#include "carddatagenerator.h"
#include "card.h"

namespace l5r
{
   class cardgenerator
   {
      public:
         cardgenerator();
         ~cardgenerator();

         CardDataSharedPtr generateCard(std::string c);

         CardSharedPtr getCard(std::string id);

      private:
         CardDataGenerator generator;
   };
};

#endif //_CARDGENERATOR_H_
