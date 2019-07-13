#ifndef _CARD_H_
#define _CARD_H_

#include <memory>
#include <carddata.h>

namespace l5r
{
   class Card
   {
      public:
         Card(CardDataSharedPtr data);
         ~Card();

         const CardDataSharedPtr data;

      private:
         std::string cardId;
   };
   
   typedef std::shared_ptr<Card> CardSharedPtr;
};

#endif //_CARD_H_
