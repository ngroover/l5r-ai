#include "carddata.h"
#include <stdexcept>

using namespace l5r;

CardData::CardData(std::string name, std::string id, cardtype type,
      bool canBeStronghold, int provinceStr,
      int strongholdHonor, int fateCost,
      int strongholdFate, deckside side,
      int militarySkill,
      int politicalSkill, int glory,
      bool militaryDash, bool politicalDash,
      int holdingBonus, clantype clan,
      int influenceCost, int influencePool) :
      name(name), id(id), type(type),
      canBeStronghold(canBeStronghold), provinceStr(provinceStr),
      strongholdHonor(strongholdHonor), fateCost(fateCost),
      strongholdFate(strongholdFate), side(side),
      militarySkill(militarySkill),
      politicalSkill(politicalSkill), glory(glory),
      militaryDash(militaryDash), politicalDash(politicalDash),
      holdingBonus(holdingBonus), clan(clan),
      influenceCost(influenceCost), influencePool(influencePool)
{
}

CardData::~CardData()
{
}

