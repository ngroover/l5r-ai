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

   enum class dynastycardtype
   {
      none,
      character,
      holding
   };

   class card
   {
      public:
         class builder;

         card(std::string name, cardtype type,
              bool canBeStronghold,
              int provinceStr,
              int strongholdHonor,
              int fateCost,
              dynastycardtype dynastyType);
         ~card();

         std::string getName() const;
         cardtype getType() const;
         int getStrongholdHonor() const;
         int getFateCost() const;
         dynastycardtype getDynastyType() const;

      private:
         std::string name;
         cardtype type;
         bool canBeStronghold;
         int provinceStr;
         int strongholdHonor;
         int fateCost;
         dynastycardtype dynastyType;
   };

   class card::builder
   {
      public:
         builder& setName(std::string name);
         builder& setType(cardtype type);
         builder& setCanBeStronghold(bool canBeStronghold);
         builder& setProvinceStr(int provinceStr);
         builder& setStrongholdHonor(int strongholdHonor);
         builder& setFateCost(int fateCost);
         builder& setDynastyType(dynastycardtype dynastyType);

         card build() const;

      private:
         std::string name = "Invalid";
         cardtype type = cardtype::invalid;
         bool canBeStronghold = true;
         int provinceStr = 0;
         int strongholdHonor = 0;
         int fateCost = 0;
         dynastycardtype dynastyType = dynastycardtype::none;
   };
};

#endif //_CARD_H_
