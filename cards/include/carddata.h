#ifndef _CARD_DATA_H_
#define _CARD_DATA_H_

#include <string>
#include <memory>

namespace l5r
{
   enum class cardtype
   {
      stronghold,
      role,
      province,
      character,
      holding,
      event,
      attachment,
      invalid
   };

   enum class deckside
   {
      dynasty,
      conflict,
      role,
      province,
      none
   };

   enum class clantype
   {
      lion,
      crab,
      dragon,
      phoenix,
      scorpion,
      crane,
      unicorn,
      neutral
   };

   class CardData
   {
      public:
         CardData(std::string name, std::string id, cardtype type,
              bool canBeStronghold, int provinceStr,
              int strongholdHonor, int fateCost,
              int strongholdFate, deckside side,
              int militarySkill,
              int politicalSkill, int glory,
              bool miiltaryDash, bool politicalDash,
              int holdingBonus, clantype clan, int influenceCost,
              int influencePool);

         ~CardData();

         const std::string name;

         const std::string id;

         const cardtype type;

         const bool canBeStronghold;

         const int provinceStr;

         const int strongholdHonor;

         const int fateCost;

         const int strongholdFate;

         const deckside side;

         const int militarySkill;

         const int politicalSkill;

         const int glory;

         const bool militaryDash;

         const bool politicalDash;

         const int holdingBonus;

         const clantype clan;

         const int influenceCost;
         
         const int influencePool;
   };

   typedef std::shared_ptr<CardData> CardDataSharedPtr;
};

#endif //_CARD_DATA_H_
