#ifndef _PROVINCE_H_
#define _PROVINCE_H_

namespace l5r
{
   enum class provinceCardStatus
   {
      unrevealed,
      revealed,
      broken
   };

   class provinceStack
   {
      public:
         provinceStack();
         ~provinceStack();

         friend bool operator==(const provinceStack &ps, const provinceStack &ps2);

         int provinceCard;
         int dynastyCard;
         bool facedownDynasty;
         provinceCardStatus provinceStatus;
   };
   bool operator==(const provinceStack &ps, const provinceStack &ps2);
};
#endif // _PROVINCE_H_
