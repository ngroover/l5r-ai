#include "cardgenerator.h"

using namespace l5r;

cardgenerator::cardgenerator()
{
}

cardgenerator::~cardgenerator()
{
}

card cardgenerator::generateCard(cards c)
{
   switch(c)
   {
      case cards::shizuka_toshi:
         return card::builder{}
               .setName("Shizuka Toshi")
               .setType(cardtype::stronghold)
               .setHoldingBonus(2)
               .setStrongholdHonor(11)
               .build();
      case cards::yojin_no_shiro:
         return card::builder{}
               .setName("Yojin No Shiro")
               .setType(cardtype::stronghold)
               .setHoldingBonus(2)
               .setStrongholdHonor(12)
               .build();
      case cards::the_art_of_peace:
         return card::builder{}
               .setName("The Art of Peace")
               .setType(cardtype::province)
               .setProvinceStr(4)
               .build();
      case cards::entrenched_position:
         return card::builder{}
               .setName("Entrenched Position")
               .setType(cardtype::province)
               .setProvinceStr(5)
               .build();
      case cards::night_raid:
         return card::builder{}
               .setName("Night Raid")
               .setType(cardtype::province)
               .setProvinceStr(4)
               .build();
      case cards::rally_to_the_cause:
         return card::builder{}
               .setName("Rally to the Cause")
               .setType(cardtype::province)
               .setProvinceStr(4)
               .build();
      case cards::shameful_display:
         return card::builder{}
               .setName("Shameful Display")
               .setType(cardtype::province)
               .setProvinceStr(3)
               .build();
      case cards::the_art_of_war:
         return card::builder{}
               .setName("The Art of War")
               .setType(cardtype::province)
               .setProvinceStr(3)
               .build();
      case cards::ancestral_lands:
         return card::builder{}
               .setName("Ancestral Lands")
               .setType(cardtype::province)
               .setProvinceStr(5)
               .build();
      case cards::manicured_gardens:
         return card::builder{}
               .setName("Manicured Garden")
               .setType(cardtype::province)
               .setProvinceStr(4)
               .build();
      case cards::meditations_on_the_tao:
         return card::builder{}
               .setName("Meditations on the Tao")
               .setType(cardtype::province)
               .setProvinceStr(4)
               .build();
      case cards::pilgrimage:
         return card::builder{}
               .setName("Pilgrimage")
               .setType(cardtype::province)
               .setProvinceStr(5)
               .build();
      case cards::asahina_artisan:
         return card::builder{}
               .setName("Asahina Artisan")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setGlory(2)
               .build();
      case cards::asahina_storyteller:
         return card::builder{}
               .setName("Asahina Storyteller")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(4)
               .setMilitarySkill(2)
               .setPoliticalSkill(4)
               .setGlory(2)
               .build();
      case cards::brash_samurai:
         return card::builder{}
               .setName("Brash Samurai")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(2)
               .setPoliticalSkill(1)
               .setGlory(2)
               .build();
      case cards::cautious_scout:
         return card::builder{}
               .setName("Cautious Scout")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(2)
               .setGlory(1)
               .build();
      case cards::daidoji_nerishma:
         return card::builder{}
               .setName("Daidoji Nerishma")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(3)
               .setPoliticalSkill(1)
               .setGlory(1)
               .build();
      case cards::doji_challenger:
         return card::builder{}
               .setName("Doji Challenger")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(3)
               .setPoliticalSkill(3)
               .setGlory(2)
               .build();
      case cards::doji_gift_giver:
         return card::builder{}
               .setName("Doji Gift Giver")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setPoliticalSkill(2)
               .setGlory(1)
               .build();
      case cards::doji_hotaru:
         return card::builder{}
               .setName("Doji Hotaru")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(5)
               .setMilitarySkill(3)
               .setPoliticalSkill(6)
               .setGlory(3)
               .build();
      case cards::doji_whisperer:
         return card::builder{}
               .setName("Doji Whisperer")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setPoliticalSkill(3)
               .setGlory(1)
               .build();
      case cards::guest_of_honor:
         return card::builder{}
               .setName("Guest of Honor")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(4)
               .setMilitarySkill(1)
               .setPoliticalSkill(4)
               .setGlory(1)
               .build();
      case cards::kakita_asami:
         return card::builder{}
               .setName("Kakita Asami")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(1)
               .setPoliticalSkill(3)
               .setGlory(2)
               .build();
      case cards::kakita_kaezin:
         return card::builder{}
               .setName("Kakita Kaezin")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(3)
               .setPoliticalSkill(2)
               .setGlory(2)
               .build();
      case cards::savvy_politician:
         return card::builder{}
               .setName("Savvy Politician")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(1)
               .setPoliticalSkill(2)
               .setGlory(1)
               .build();
      case cards::artisan_academy:
         return card::builder{}
               .setName("Artisan Academy")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::holding)
               .setHoldingBonus(1)
               .build();
      case cards::otomo_courtier:
         return card::builder{}
               .setName("Otomo Courtier")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setMilitaryDash(true)
               .setPoliticalSkill(2)
               .setGlory(1)
               .build();
      case cards::miya_mystic:
         return card::builder{}
               .setName("Miya Mystic")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(1)
               .setPoliticalSkill(1)
               .setGlory(1)
               .build();
      case cards::favorable_ground:
         return card::builder{}
               .setName("Favorable Ground")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::holding)
               .setHoldingBonus(1)
               .build();
      case cards::imperial_storehouse:
         return card::builder{}
               .setName("Imperial Storehouse")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::holding)
               .setHoldingBonus(1)
               .build();
      case cards::seppun_guardsman:
         return card::builder{}
               .setName("Seppun Guardsman")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setMilitarySkill(2)
               .setPoliticalDash(true)
               .setGlory(1)
               .build();
      case cards::wandering_ronin:
         return card::builder{}
               .setName("Wandering Ronin")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(2)
               .setPoliticalSkill(2)
               .build();
      case cards::akodo_gunso:
         return card::builder{}
               .setName("Akodo Gunso")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(2)
               .setPoliticalSkill(1)
               .setGlory(2)
               .build();
      case cards::akodo_toturi:
         return card::builder{}
               .setName("Akodo Toturi")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(5)
               .setMilitarySkill(6)
               .setPoliticalSkill(3)
               .setGlory(3)
               .build();
      case cards::deathseeker:
         return card::builder{}
               .setName("Deathseeker")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitarySkill(2)
               .setPoliticalSkill(1)
               .build();
      case cards::honored_general:
         return card::builder{}
               .setName("Honored General")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(4)
               .setMilitarySkill(3)
               .setPoliticalSkill(1)
               .setGlory(2)
               .build();
      case cards::ikoma_eiji:
         return card::builder{}
               .setName("Ikoma Eiji")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(4)
               .setMilitarySkill(1)
               .setPoliticalSkill(3)
               .setGlory(3)
               .build();
      case cards::ikoma_prodigy:
         return card::builder{}
               .setName("Ikoma Prodigy")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setPoliticalSkill(2)
               .setGlory(1)
               .build();
      case cards::kitsu_spiritcaller:
         return card::builder{}
               .setName("Kitsu Spiritcaller")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(1)
               .setPoliticalSkill(3)
               .setGlory(2)
               .build();
      case cards::lions_pride_brawler:
         return card::builder{}
               .setName("Lions Pride Brawler")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(3)
               .setPoliticalSkill(2)
               .setGlory(1)
               .build();
      case cards::matsu_beiona:
         return card::builder{}
               .setName("Matsu Beiona")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(3)
               .setMilitarySkill(3)
               .setPoliticalSkill(2)
               .setGlory(2)
               .build();
      case cards::matsu_berserker:
         return card::builder{}
               .setName("Matsu Berserker")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setMilitarySkill(3)
               .setPoliticalDash(true)
               .setGlory(1)
               .build();
      case cards::obstinate_recruit:
         return card::builder{}
               .setName("Obstinate Recruit")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(0)
               .setMilitarySkill(2)
               .build();
      case cards::staging_ground:
         return card::builder{}
               .setName("Staging Ground")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::holding)
               .setHoldingBonus(1)
               .build();
      case cards::steadfast_samurai:
         return card::builder{}
               .setName("Steadfast Samurai")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(1)
               .setMilitarySkill(1)
               .setPoliticalSkill(1)
               .setGlory(1)
               .build();
      case cards::venerable_historian:
         return card::builder{}
               .setName("Venerable Historian")
               .setType(cardtype::dynasty)
               .setDynastyType(dynastycardtype::character)
               .setFateCost(2)
               .setMilitaryDash(true)
               .setPoliticalSkill(1)
               .setGlory(3)
               .build();
      case cards::above_question:
         return card::builder{}
               .setName("Above Question")
               .setType(cardtype::conflict)
               .build();
      case cards::duelist_training:
         return card::builder{}
               .setName("Duelist Training")
               .setType(cardtype::conflict)
               .build();
      case cards::height_of_fashion:
         return card::builder{}
               .setName("Height of Fashion")
               .setType(cardtype::conflict)
               .build();
      case cards::steward_of_law:
         return card::builder{}
               .setName("Steward of Law")
               .setType(cardtype::conflict)
               .build();
      case cards::admit_defeat:
         return card::builder{}
               .setName("Admit Defeat")
               .setType(cardtype::conflict)
               .build();
      case cards::noble_sacrifice:
         return card::builder{}
               .setName("Noble Sacrifice")
               .setType(cardtype::conflict)
               .build();
      case cards::the_perfect_gift:
         return card::builder{}
               .setName("The Perfect Gift")
               .setType(cardtype::conflict)
               .build();
      case cards::voice_of_honor:
         return card::builder{}
               .setName("Voice of Honor")
               .setType(cardtype::conflict)
               .build();
      case cards::way_of_the_crane:
         return card::builder{}
               .setName("Way of the Crane")
               .setType(cardtype::conflict)
               .build();
      case cards::political_rival:
         return card::builder{}
               .setName("Political Rival")
               .setType(cardtype::conflict)
               .build();
      case cards::assassination:
         return card::builder{}
               .setName("Assassination")
               .setType(cardtype::conflict)
               .build();
      case cards::banzai:
         return card::builder{}
               .setName("Banzi!")
               .setType(cardtype::conflict)
               .build();
      case cards::charge:
         return card::builder{}
               .setName("Charge!")
               .setType(cardtype::conflict)
               .build();
      case cards::contingency_plan:
         return card::builder{}
               .setName("Contingency Plan")
               .setType(cardtype::conflict)
               .build();
      case cards::court_games:
         return card::builder{}
               .setName("Court Games")
               .setType(cardtype::conflict)
               .build();
      case cards::fallen_in_battle:
         return card::builder{}
               .setName("Fallen in Battle")
               .setType(cardtype::conflict)
               .build();
      case cards::for_shame:
         return card::builder{}
               .setName("For Shame!")
               .setType(cardtype::conflict)
               .build();
      case cards::good_omen:
         return card::builder{}
               .setName("Good Omen")
               .setType(cardtype::conflict)
               .build();
      case cards::outwit:
         return card::builder{}
               .setName("Outwit")
               .setType(cardtype::conflict)
               .build();
      case cards::rout:
         return card::builder{}
               .setName("Rout")
               .setType(cardtype::conflict)
               .build();
      case cards::spies_at_court:
         return card::builder{}
               .setName("Spies at Court")
               .setType(cardtype::conflict)
               .build();
      case cards::fine_katana:
         return card::builder{}
               .setName("Fine Katana")
               .setType(cardtype::conflict)
               .build();
      case cards::ornate_fan:
         return card::builder{}
               .setName("Ornate Fan")
               .setType(cardtype::conflict)
               .build();
      case cards::cloud_the_mind:
         return card::builder{}
               .setName("Cloud the Mind")
               .setType(cardtype::conflict)
               .build();
      case cards::for_greater_glory:
         return card::builder{}
               .setName("For Greater Glory")
               .setType(cardtype::conflict)
               .build();
      case cards::guidance_of_the_ancestors:
         return card::builder{}
               .setName("Guidence of the Ancestors")
               .setType(cardtype::conflict)
               .build();
      case cards::honored_blade:
         return card::builder{}
               .setName("Honored Blade")
               .setType(cardtype::conflict)
               .build();
      case cards::master_of_the_spear:
         return card::builder{}
               .setName("Master of the Spear")
               .setType(cardtype::conflict)
               .setFateCost(3)
               .setMilitarySkill(2)
               .setPoliticalSkill(2)
               .setGlory(1)
               .build();
      case cards::ready_for_battle:
         return card::builder{}
               .setName("Ready For Battle")
               .setType(cardtype::conflict)
               .build();
      case cards::sashimono:
         return card::builder{}
               .setName("Sashimono")
               .setType(cardtype::conflict)
               .build();
      case cards::stand_your_ground:
         return card::builder{}
               .setName("Stand Your Ground")
               .setType(cardtype::conflict)
               .build();
      case cards::strength_in_numbers:
         return card::builder{}
               .setName("Strength in Numbers")
               .setType(cardtype::conflict)
               .build();
      case cards::vengeful_oathkeeper:
         return card::builder{}
               .setName("Vengeful Oathkeeper")
               .setType(cardtype::conflict)
               .setFateCost(2)
               .setMilitarySkill(2)
               .setPoliticalSkill(1)
               .setGlory(0)
               .build();
      case cards::way_of_the_lion:
         return card::builder{}
               .setName("Way of the Lion")
               .setType(cardtype::conflict)
               .build();
      default:
         throw std::runtime_error("Invalid card type");
         // throw exception
         break;
   }
}

std::map<cards,card> cardgenerator::generateCards(decklist deck)
{
   std::map<cards,card> cardMap;
   for(auto c: deck.getList())
   {
      if( cardMap.find(c) == cardMap.end() )
      {
         cardMap.insert(std::pair<cards,card>(c,generateCard(c)));
      }
   }
   return cardMap;
}

