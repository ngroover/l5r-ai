#include "cardgenerator.h"

using namespace l5r;

cardgenerator::cardgenerator() : generator("./cards/data")
{
}

cardgenerator::~cardgenerator()
{
}

std::string cardgenerator::getStringId(cards c)
{
   switch(c)
   {
      case cards::shizuka_toshi:
         return "shizuka-toshi";
      case cards::yojin_no_shiro:
         return "yojin-no-shiro";
      case cards::the_art_of_peace:
         return "the-art-of-peace";
      case cards::entrenched_position:
         return "entrenched-position";
      case cards::night_raid:
         return "night-raid";
      case cards::rally_to_the_cause:
         return "rally-to-the-cause";
      case cards::shameful_display:
         return "shameful-display";
      case cards::the_art_of_war:
         return "the-art-of-war";
      case cards::ancestral_lands:
         return "ancestral-lands";
      case cards::manicured_garden:
         return "manicured-garden";
      case cards::meditations_on_the_tao:
         return "meditations-on-the-tao";
      case cards::pilgrimage:
         return "pilgrimage";
      case cards::asahina_artisan:
         return "asahina-artisan";
      case cards::asahina_storyteller:
         return "asahina-storyteller";
      case cards::brash_samurai:
         return "brash-samurai";
      case cards::cautious_scout:
         return "cautious-scout";
      case cards::daidoji_nerishma:
         return "daidoji-nerishma";
      case cards::doji_challenger:
         return "doji-challenger";
      case cards::doji_gift_giver:
         return "doji-gift-giver";
      case cards::doji_hotaru:
         return "doji-hotaru";
      case cards::doji_whisperer:
         return "doji-whisperer";
      case cards::guest_of_honor:
         return "guest-of-honor";
      case cards::kakita_asami:
         return "kakita-asami";
      case cards::kakita_kaezin:
         return "kakita-kaezin";
      case cards::savvy_politician:
         return "savvy-politician";
      case cards::artisan_academy:
         return "artisan-academy";
      case cards::otomo_courtier:
         return "otomo-courtier";
      case cards::miya_mystic:
         return "miya-mystic";
      case cards::favorable_ground:
         return "favorable-ground";
      case cards::imperial_storehouse:
         return "imperial-storehouse";
      case cards::seppun_guardsman:
         return "seppun-guardsman";
      case cards::wandering_ronin:
         return "wandering-ronin";
      case cards::akodo_gunso:
         return "akodo-gunso";
      case cards::akodo_toturi:
         return "akodo-toturi";
      case cards::deathseeker:
         return "deathseeker";
      case cards::honored_general:
         return "honored-general";
      case cards::ikoma_eiji:
         return "ikoma-eiji";
      case cards::ikoma_prodigy:
         return "ikoma-prodigy";
      case cards::kitsu_spiritcaller:
         return "kitsu-spiritcaller";
      case cards::lions_pride_brawler:
         return "lion-s-pride-brawler";
      case cards::matsu_beiona:
         return "matsu-beiona";
      case cards::matsu_berserker:
         return "matsu-berserker";
      case cards::obstinate_recruit:
         return "obstinate-recruit";
      case cards::staging_ground:
         return "staging-ground";
      case cards::steadfast_samurai:
         return "steadfast-samurai";
      case cards::venerable_historian:
         return "venerable-historian";
      case cards::above_question:
         return "above-question";
      case cards::duelist_training:
         return "duelist-training";
      case cards::height_of_fashion:
         return "height-of-fashion";
      case cards::steward_of_law:
         return "steward-of-law";
      case cards::admit_defeat:
         return "admit-defeat";
      case cards::noble_sacrifice:
         return "noble-sacrifice";
      case cards::the_perfect_gift:
         return "the-perfect-gift";
      case cards::voice_of_honor:
         return "voice-of-honor";
      case cards::way_of_the_crane:
         return "way-of-the-crane";
      case cards::political_rival:
         return "political-rival";
      case cards::assassination:
         return "assassination";
      case cards::banzai:
         return "banzai";
      case cards::charge:
         return "charge";
      case cards::contingency_plan:
         return "contingency-plan";
      case cards::court_games:
         return "court-games";
      case cards::fallen_in_battle:
         return "fallen-in-battle";
      case cards::for_shame:
         return "for-shame";
      case cards::good_omen:
         return "good-omen";
      case cards::outwit:
         return "outwit";
      case cards::rout:
         return "rout";
      case cards::spies_at_court:
         return "spies-at-court";
      case cards::fine_katana:
         return "fine-katana";
      case cards::ornate_fan:
         return "ornate-fan";
      case cards::cloud_the_mind:
         return "cloud-the-mind";
      case cards::for_greater_glory:
         return "for-greater-glory";
      case cards::guidance_of_the_ancestors:
         return "guidance-of-the-ancestors";
      case cards::honored_blade:
         return "honored-blade";
      case cards::master_of_the_spear:
         return "master-of-the-spear";
      case cards::ready_for_battle:
         return "ready-for-battle";
      case cards::sashimono:
         return "sashimono";
      case cards::stand_your_ground:
         return "stand-your-ground";
      case cards::strength_in_numbers:
         return "strength-in-numbers";
      case cards::vengeful_oathkeeper:
         return "vengeful-oathkeeper";
      case cards::way_of_the_lion:
         return "way-of-the-lion";
      default:
         throw std::runtime_error("Invalid card type");
         // throw exception
         break;
   }
}

CardDataSharedPtr cardgenerator::generateCard(cards c)
{
   return generator.generateCard(getStringId(c));
}

std::map<cards,CardDataSharedPtr> cardgenerator::generateCards(decklist deck)
{
   std::map<cards,CardDataSharedPtr> cardMap;
   for(auto c: deck.getList())
   {
      if( cardMap.find(c) == cardMap.end() )
      {
         cardMap.insert(std::pair<cards,CardDataSharedPtr>(c,generateCard(c)));
      }
   }
   return cardMap;
}

