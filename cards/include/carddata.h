#ifndef _CARD_DATA_H_
#define _CARD_DATA_H_

#include <string>

namespace l5r
{
   /** An enum describing the type of card.
   */
   enum class cardtype
   {
      stronghold,
      role,
      province,
      dynasty,
      conflict,
      invalid
   };

   /** An enum describing a type of dynasty card
   */
   enum class dynastycardtype
   {
      none,
      character,
      holding
   };

   /** @brief An immutable class containing a card's static data.
   
      Any data that does not change during the course of the game (such as
      base military/political skill or fate cost) should go here.
      This class saves some memory by avoiding having to store bits
      of constant data with each card in the game.  Each instance
      of a particular Card in the game can simply reference a
      CardData object for it's constant data.

      The builder class should make it easier to construct a CardData object
      but you can use the CardGenerator class to generate the CardData object
      from a card id.
   */
   class CardData
   {
      public:
         class builder;

         /** @brief Constructor for CardData. Use builder class for easier construction.
         */
         CardData(std::string name, cardtype type,
              bool canBeStronghold, int provinceStr,
              int strongholdHonor, int fateCost,
              dynastycardtype dynastyType, int militarySkill,
              int politicalSkill, int glory,
              bool miiltaryDash, bool politicalDash,
              int holdingBonus);

         /** @brief Deconstructor
         */
         ~CardData();

         const std::string name;
         const cardtype type;
         const bool canBeStronghold;
         const int provinceStr;
         const int strongholdHonor;
         const int fateCost;
         const dynastycardtype dynastyType;
         const int militarySkill;
         const int politicalSkill;
         const int glory;
         const bool militaryDash;
         const bool politicalDash;
         const int holdingBonus;
   };

   /** @brief The builder class should make it easier to construct a CardData object.
      
      To construct a CardData object from a card id see the CardGenerator class.
   */
   class CardData::builder
   {
      public:

         /** @brief Set the card name. The text shown on the actual card.
         */
         builder& setName(std::string name);

         /** @brief Set the card type
         */
         builder& setType(cardtype type);

         /** @brief Set a boolean if card can be chosen as a stronghold province
         */
         builder& setCanBeStronghold(bool canBeStronghold);

         /** @brief Set the strength of a province 
         */
         builder& setProvinceStr(int provinceStr);

         /** @brief Set starting honor a stronghold provides
         */
         builder& setStrongholdHonor(int strongholdHonor);

         /** @brief Set the fate cost to play the card
         */
         builder& setFateCost(int fateCost);

         /** @brief Set the type of dynasty card. (Only applies if type is dynastycard)
         */
         builder& setDynastyType(dynastycardtype dynastyType);

         /** @brief Set base military skill of character
         */
         builder& setMilitarySkill(int militarySkill);

         /** @brief Set base political skill of character
         */
         builder& setPoliticalSkill(int politicalSkill);

         /** @brief Set base glory skill of character
         */
         builder& setGlory(int glory);

         /** @brief Set boolean indicating a military dash on character (military skill ignored)
         */
         builder& setMilitaryDash(bool militaryDash);

         /** @brief Set boolean indicating a political dash on character (political skill ignored)
         */
         builder& setPoliticalDash(bool politicalDash);

         /** @brief Set defensive bonus provided by holdings. (Only applies if type is holding)
         */
         builder& setHoldingBonus(int holdingBonus);

         /** @brief Returns CardData object
         */
         CardData build() const;

      private:
         std::string name;
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
         int holdingBonus = 0;
   };
};

#endif //_CARD_DATA_H_
