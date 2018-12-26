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
              dynastycardtype dynastyType,
              int militarySkill,
              int politicalSkill,
              int glory,
              bool miiltaryDash,
              bool politicalDash);
         card(){};
         ~card();

         std::string getName() const;
         cardtype getType() const;
         int getStrongholdHonor() const;
         int getFateCost() const;
         dynastycardtype getDynastyType() const;
         int getMilitarySkill() const;
         int getPoliticalSkill() const;
         int getGlory() const;
         bool getMilitaryDash() const;
         bool getPoliticalDash() const;

      private:
         std::string name;
         cardtype type;
         bool canBeStronghold;
         int provinceStr;
         int strongholdHonor;
         int fateCost;
         dynastycardtype dynastyType;
         int militarySkill;
         int politicalSkill;
         int glory;
         bool militaryDash;
         bool politicalDash;
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
         builder& setMilitarySkill(int militarySkill);
         builder& setPoliticalSkill(int politicalSkill);
         builder& setGlory(int glory);
         builder& setMilitaryDash(bool militaryDash);
         builder& setPoliticalDash(bool politicalDash);

         card build() const;

      private:
         std::string name = "Invalid";
         cardtype type = cardtype::invalid;
         bool canBeStronghold = true;
         int provinceStr = 0;
         int strongholdHonor = 0;
         int fateCost = 0;
         int militarySkill = 0;
         int politicalSkill = 0;
         int glory = 0;
         bool militaryDash = false;
         bool politicalDash = false;
         dynastycardtype dynastyType = dynastycardtype::none;
   };
};

#endif //_CARD_H_
