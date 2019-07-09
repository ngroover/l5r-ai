#include "cardgenerator.h"

using namespace l5r;

cardgenerator::cardgenerator() : generator("./cards/data")
{
}

cardgenerator::~cardgenerator()
{
}

cards cardgenerator::fromStringId(std::string c)
{
   if(c == "shizuka-toshi")
      return cards::shizuka_toshi;
   if(c == "yojin-no-shiro")
      return cards::yojin_no_shiro;
   if(c == "the-art-of-peace")
      return cards::the_art_of_peace;
   if(c == "entrenched-position")
      return cards::entrenched_position;
   if(c == "night-raid")
      return cards::night_raid;
   if(c == "rally-to-the-cause")
      return cards::rally_to_the_cause;
   if(c == "shameful-display")
      return cards::shameful_display;
   if(c == "the-art-of-war")
      return cards::the_art_of_war;
   if(c == "ancestral-lands")
      return cards::ancestral_lands;
   if(c == "manicured-garden")
      return cards::manicured_garden;
   if(c == "meditations-on-the-tao")
      return cards::meditations_on_the_tao;
   if(c == "pilgrimage")
      return cards::pilgrimage;
   if(c == "asahina-artisan")
      return cards::asahina_artisan;
   if(c == "asahina-storyteller")
      return cards::asahina_storyteller;
   if(c == "brash-samurai")
      return cards::brash_samurai;
   if(c == "cautious-scout")
      return cards::cautious_scout;
   if(c == "daidoji-nerishma")
      return cards::daidoji_nerishma;
   if(c == "doji-challenger")
      return cards::doji_challenger;
   if(c == "doji-gift-giver")
      return cards::doji_gift_giver;
   if(c == "doji-hotaru")
      return cards::doji_hotaru;
   if(c == "doji-whisperer")
      return cards::doji_whisperer;
   if(c == "guest-of-honor")
      return cards::guest_of_honor;
   if(c == "kakita-asami")
      return cards::kakita_asami;
   if(c == "kakita-kaezin")
      return cards::kakita_kaezin;
   if(c == "savvy-politician")
      return cards::savvy_politician;
   if(c == "artisan-academy")
      return cards::artisan_academy;
   if(c == "otomo-courtier")
      return cards::otomo_courtier;
   if(c == "miya-mystic")
      return cards::miya_mystic;
   if(c == "favorable-ground")
      return cards::favorable_ground;
   if(c == "imperial-storehouse")
      return cards::imperial_storehouse;
   if(c == "seppun-guardsman")
      return cards::seppun_guardsman;
   if(c == "wandering-ronin")
      return cards::wandering_ronin;
   if(c == "akodo-gunso")
      return cards::akodo_gunso;
   if(c == "akodo-toturi")
      return cards::akodo_toturi;
   if(c == "deathseeker")
      return cards::deathseeker;
   if(c == "honored-general")
      return cards::honored_general;
   if(c == "ikoma-eiji")
      return cards::ikoma_eiji;
   if(c == "ikoma-prodigy")
      return cards::ikoma_prodigy;
   if(c == "kitsu-spiritcaller")
      return cards::kitsu_spiritcaller;
   if(c == "lion-s-pride-brawler")
      return cards::lions_pride_brawler;
   if(c == "matsu-beiona")
      return cards::matsu_beiona;
   if(c == "matsu-berserker")
      return cards::matsu_berserker;
   if(c == "obstinate-recruit")
      return cards::obstinate_recruit;
   if(c == "staging-ground")
      return cards::staging_ground;
   if(c == "steadfast-samurai")
      return cards::steadfast_samurai;
   if(c == "venerable-historian")
      return cards::venerable_historian;
   if(c == "above-question")
      return cards::above_question;
   if(c == "duelist-training")
      return cards::duelist_training;
   if(c == "height-of-fashion")
      return cards::height_of_fashion;
   if(c == "steward-of-law")
      return cards::steward_of_law;
   if(c == "admit-defeat")
      return cards::admit_defeat;
   if(c == "noble-sacrifice")
      return cards::noble_sacrifice;
   if(c == "the-perfect-gift")
      return cards::the_perfect_gift;
   if(c == "voice-of-honor")
      return cards::voice_of_honor;
   if(c == "way-of-the-crane")
      return cards::way_of_the_crane;
   if(c == "political-rival")
      return cards::political_rival;
   if(c == "assassination")
      return cards::assassination;
   if(c == "banzai")
      return cards::banzai;
   if(c == "charge")
      return cards::charge;
   if(c == "contingency-plan")
      return cards::contingency_plan;
   if(c == "court-games")
      return cards::court_games;
   if(c == "fallen-in-battle")
      return cards::fallen_in_battle;
   if(c == "for-shame")
      return cards::for_shame;
   if(c == "good-omen")
      return cards::good_omen;
   if(c == "outwit")
      return cards::outwit;
   if(c == "rout")
      return cards::rout;
   if(c == "spies-at-court")
      return cards::spies_at_court;
   if(c == "fine-katana")
      return cards::fine_katana;
   if(c == "ornate-fan")
      return cards::ornate_fan;
   if(c == "cloud-the-mind")
      return cards::cloud_the_mind;
   if(c == "for-greater-glory")
      return cards::for_greater_glory;
   if(c == "guidance-of-the-ancestors")
      return cards::guidance_of_the_ancestors;
   if(c == "honored-blade")
      return cards::honored_blade;
   if(c == "master-of-the-spear")
      return cards::master_of_the_spear;
   if(c == "ready-for-battle")
      return cards::ready_for_battle;
   if(c == "sashimono")
      return cards::sashimono;
   if(c == "stand-your-ground")
      return cards::stand_your_ground;
   if(c == "strength-in-numbers")
      return cards::strength_in_numbers;
   if(c == "vengeful-oathkeeper")
      return cards::vengeful_oathkeeper;
   if(c == "way-of-the-lion")
      return cards::way_of_the_lion;
   if(c == "fertile-fields")
      return cards::fertile_fields;
   if(c == "seeker-of-air")
      return cards::seeker_of_air;
   if(c == "keeper-of-water")
      return cards::keeper_of_water;
   if(c == "keeper-initiate")
      return cards::keeper_initiate;
   if(c == "seeker-initiate")
      return cards::seeker_initiate;
   if(c == "iuchi-wayfinder")
      return cards::iuchi_wayfinder;
   if(c == "ide-messenger")
      return cards::ide_messenger;
   if(c == "favored-mount")
      return cards::favored_mount;
   if(c == "spyglass")
      return cards::spyglass;
   if(c == "breakthrough")
      return cards::breakthrough;
   if(c == "captive-audience")
      return cards::captive_audience;
   if(c == "display-of-power")
      return cards::display_of_power;
   if(c == "seeker-of-knowledge")
      return cards::seeker_of_knowledge;
   if(c == "magnificent-kimono")
      return cards::magnificent_kimono;
   if(c == "pacifism")
      return cards::pacifism;
   if(c == "know-the-world")
      return cards::know_the_world;

   throw std::runtime_error("Didn't match "+c);
}

CardDataSharedPtr cardgenerator::generateCard(std::string c)
{
   return generator.generateCard(c);
}

std::map<cards,CardDataSharedPtr> cardgenerator::generateCards(Decklist deck)
{
   std::map<cards,CardDataSharedPtr> cardMap;
   for(auto c: deck.getList())
   {
      if( cardMap.find(fromStringId(c)) == cardMap.end() )
      {
         cardMap.insert(std::pair<cards,CardDataSharedPtr>(fromStringId(c),generateCard(c)));
      }
   }
   return cardMap;
}

