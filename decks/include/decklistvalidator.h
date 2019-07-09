#ifndef _DECKLIST_VALIDATOR_H_
#define _DECKLIST_VALIDATOR_H_

#include <string>
#include <map>
#include "decklist.h"
#include "carddatagenerator.h"

namespace l5r
{
   class DecklistValidator
   {
      public:
         DecklistValidator(CardDataGeneratorSharedPtr cardData);
         ~DecklistValidator();

         bool isDeckValid(const Decklist &deck);

         std::string getInvalidReason();

      private:
         CardDataGeneratorSharedPtr cardData;
         std::string reasonString;
   };
};

#endif //_DECKLIST_VALIDATOR_H_
