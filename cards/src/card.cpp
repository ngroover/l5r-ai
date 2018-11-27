#include "card.h"

using namespace l5r;

card::card(std::string name, cardtype type,
      bool canBeStronghold,
      int provinceStr) :
      name(name), type(type),
      canBeStronghold(canBeStronghold),
      provinceStr(provinceStr)
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
   return card(name, type, canBeStronghold,
      provinceStr);
}
