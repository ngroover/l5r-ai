#include "card.h"

using namespace l5r;

card::card(std::string name, cardtype type,
      bool canBeStronghold,
      int provinceStr,
      int strongholdHonor,
      int fateCost,
      dynastycardtype dynastyType) :
      name(name), type(type),
      canBeStronghold(canBeStronghold),
      provinceStr(provinceStr),
      strongholdHonor(strongholdHonor),
      fateCost(fateCost),
      dynastyType(dynastyType)
{
}

card::~card()
{
}

std::string card::getName() const
{
   return name;
}

cardtype card::getType() const
{
   return type;
}

int card::getStrongholdHonor() const
{
  return strongholdHonor;
}

int card::getFateCost() const
{
  return fateCost;
}

dynastycardtype card::getDynastyType() const
{
   return dynastyType;
}

card::builder& card::builder::setName(std::string name)
{
   this->name = name;
   return *this;
}

card::builder& card::builder::setType(cardtype type)
{
   this->type = type;
   return *this;
}

card::builder& card::builder::setCanBeStronghold(bool canBeStronghold)
{
   this->canBeStronghold = canBeStronghold;
   return *this;
}

card::builder& card::builder::setProvinceStr(int provinceStr)
{
   this->provinceStr = provinceStr;
   return *this;
}

card::builder& card::builder::setStrongholdHonor(int strongholdHonor)
{
   this->strongholdHonor = strongholdHonor;
   return *this;
}

card::builder& card::builder::setFateCost(int fateCost)
{
   this->fateCost = fateCost;
   return *this;
}

card::builder& card::builder::setDynastyType(dynastycardtype dynastyType)
{
   this->dynastyType = dynastyType;
   return *this;
}

card card::builder::build() const
{
   if( name == "Invalid" )
   {
      throw "Invalid card name";
   }
   if( type == cardtype::invalid )
   {
      throw "Invalid card type";
   }
   if ( type == cardtype::dynasty && 
      dynastyType == dynastycardtype::none)
   {
      throw "Invalid dynasty card type";
   }
   return card(name, type, canBeStronghold,
      provinceStr, strongholdHonor,
      fateCost,dynastyType);
}
