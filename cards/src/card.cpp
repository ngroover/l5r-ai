#include "card.h"
#include <stdexcept>

using namespace l5r;

card::card(std::string name, cardtype type,
      bool canBeStronghold,
      int provinceStr,
      int strongholdHonor,
      int fateCost,
      dynastycardtype dynastyType,
      int militarySkill,
      int politicalSkill,
      int glory,
      bool militaryDash,
      bool politicalDash) :
      name(name), type(type),
      canBeStronghold(canBeStronghold),
      provinceStr(provinceStr),
      strongholdHonor(strongholdHonor),
      fateCost(fateCost),
      dynastyType(dynastyType),
      militarySkill(militarySkill),
      politicalSkill(politicalSkill),
      glory(glory),
      militaryDash(militaryDash),
      politicalDash(politicalDash)
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

int card::getMilitarySkill() const
{
   return militarySkill;
}

int card::getPoliticalSkill() const
{
   return politicalSkill;
}

int card::getGlory() const
{
   return glory;
}

bool card::getMilitaryDash() const
{
   return militaryDash;
}

bool card::getPoliticalDash() const
{
   return politicalDash;
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

card::builder& card::builder::setMilitarySkill(int militarySkill)
{
   this->militarySkill = militarySkill;
   return *this;
}

card::builder& card::builder::setPoliticalSkill(int politicalSkill)
{
   this->politicalSkill = politicalSkill;
   return *this;
}

card::builder& card::builder::setGlory(int glory)
{
   this->glory = glory;
   return *this;
}

card::builder& card::builder::setMilitaryDash(bool militaryDash)
{
   this->militaryDash = militaryDash;
   return *this;
}

card::builder& card::builder::setPoliticalDash(bool politcalDash)
{
   this->politicalDash = politicalDash;
   return *this;
}

card card::builder::build() const
{
   if( name == "Invalid" )
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
   return card(name, type, canBeStronghold,
      provinceStr, strongholdHonor,
      fateCost,dynastyType, militarySkill, politicalSkill, glory,
      militaryDash, politicalDash);
}
