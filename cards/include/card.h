#ifndef _CARD_H_
#define _CARD_H_

#include <string>

namespace l5r
{
   enum class cardtype
   {
      stronghold,
      role,
      province,
      dynasty,
      conflict,
      invalid
   };

   class card
   {
      public:
         class builder;

         card(std::string name, cardtype type,
              bool canBeStronghold,
              int provinceStr,
              int strongholdHonor);
         ~card();

         std::string getName() const;
         cardtype getType() const;
         int getStrongholdHonor() const;

      private:
         std::string name;
         cardtype type;
         bool canBeStronghold;
         int provinceStr;
         int strongholdHonor;
   };

   class card::builder
   {
      public:
         builder& setName(std::string name);
         builder& setType(cardtype type);
         builder& setCanBeStronghold(bool canBeStronghold);
         builder& setProvinceStr(int provinceStr);
         builder& setStrongholdHonor(int strongholdHonor);

         card build() const;

      private:
         std::string name = "Invalid";
         cardtype type = cardtype::invalid;
         bool canBeStronghold = true;
         int provinceStr = 0;
         int strongholdHonor = 0;
   };
};

#endif //_CARD_H_
