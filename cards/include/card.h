#ifndef _CARD_H_
#define _CARD_H_

#include <memory>
#include <carddata.h>

namespace l5r
{
   enum class provinceCardStatus
   {
      unrevealed,
      revealed,
      broken
   };

   class Card
   {
      public:
         Card(CardDataSharedPtr data);
         ~Card();

         const CardDataSharedPtr data;

         // temporary until we get rid of integer based cards
         int dynastyCard;
         bool facedownDynasty;
         provinceCardStatus provinceStatus;

         int fateAttached;
         bool bowed;
      private:
         std::string cardId;
   };
   
   typedef std::shared_ptr<Card> CardSharedPtr;
};

#endif //_CARD_H_
