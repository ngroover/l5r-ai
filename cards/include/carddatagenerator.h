#ifndef _CARD_DATA_GENERATOR_H_
#define _CARD_DATA_GENERATOR_H_

#include <carddata.h>
#include <memory>
#include <map>
#include <nlohmann/json.hpp>

namespace l5r
{
   class CardDataGenerator
   {
      public:
         CardDataGenerator(std::string pathToCardData);

         ~CardDataGenerator();

         CardDataSharedPtr generateCard(std::string targetCard);

      private:
         std::map< std::string, CardDataSharedPtr> cardMap;
   };
};

#endif //_CARD_DATA_GENERATOR_H_
