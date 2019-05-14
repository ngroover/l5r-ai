#include "carddata.h"
#include <stdexcept>

using namespace l5r;

CardData::CardData(std::string name, cardtype type,
      bool canBeStronghold, int provinceStr,
      int strongholdHonor, int fateCost,
      dynastycardtype dynastyType, int militarySkill,
      int politicalSkill, int glory,
      bool militaryDash, bool politicalDash,
      int holdingBonus) :
      name(name), type(type),
      canBeStronghold(canBeStronghold), provinceStr(provinceStr),
      strongholdHonor(strongholdHonor), fateCost(fateCost),
      dynastyType(dynastyType), militarySkill(militarySkill),
      politicalSkill(politicalSkill), glory(glory),
      militaryDash(militaryDash), politicalDash(politicalDash),
      holdingBonus(holdingBonus)
{
}

CardData::~CardData()
{
}

CardData::builder& CardData::builder::setName(std::string name)
{
   this->name = name;
   return *this;
}

CardData::builder& CardData::builder::setType(cardtype type)
{
   this->type = type;
   return *this;
}

CardData::builder& CardData::builder::setCanBeStronghold(bool canBeStronghold)
{
   this->canBeStronghold = canBeStronghold;
   return *this;
}

CardData::builder& CardData::builder::setProvinceStr(int provinceStr)
{
   this->provinceStr = provinceStr;
   return *this;
}

CardData::builder& CardData::builder::setStrongholdHonor(int strongholdHonor)
{
   this->strongholdHonor = strongholdHonor;
   return *this;
}

CardData::builder& CardData::builder::setFateCost(int fateCost)
{
   this->fateCost = fateCost;
   return *this;
}

CardData::builder& CardData::builder::setDynastyType(dynastycardtype dynastyType)
{
   this->dynastyType = dynastyType;
   return *this;
}

CardData::builder& CardData::builder::setMilitarySkill(int militarySkill)
{
   this->militarySkill = militarySkill;
   return *this;
}

CardData::builder& CardData::builder::setPoliticalSkill(int politicalSkill)
{
   this->politicalSkill = politicalSkill;
   return *this;
}

CardData::builder& CardData::builder::setGlory(int glory)
{
   this->glory = glory;
   return *this;
}

CardData::builder& CardData::builder::setMilitaryDash(bool militaryDash)
{
   this->militaryDash = militaryDash;
   return *this;
}

CardData::builder& CardData::builder::setPoliticalDash(bool politcalDash)
{
   this->politicalDash = politicalDash;
   return *this;
}

CardData::builder& CardData::builder::setHoldingBonus(int holdingBonus)
{
   this->holdingBonus = holdingBonus;
   return *this;
}

CardData CardData::builder::build() const
{
   if( name == "" )
   {
      throw std::runtime_error("Invalid card name");
   }
   if( type == cardtype::invalid )
   {
      throw std::runtime_error("Invalid card type");
   }
   if ( type == cardtype::dynasty && 
      dynastyType == dynastycardtype::none)
   {
      throw std::runtime_error("Invalid dynasty card type");
   }
   return CardData(name, type, canBeStronghold,
      provinceStr, strongholdHonor,
      fateCost,dynastyType, militarySkill, politicalSkill, glory,
      militaryDash, politicalDash,holdingBonus);
}

