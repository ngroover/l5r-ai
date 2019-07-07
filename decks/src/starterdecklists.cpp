#include "starterdecklists.h"
#include "decklist.h"
#include "cards.h"

using namespace l5r;

namespace l5r
{
   std::vector<decklist> decklists = 
   {
      {"Lion Starter Deck", 
         {
            // stronghold
            cards::yojin_no_shiro,

            // provinces
            cards::the_art_of_war,
            cards::ancestral_lands,
            cards::manicured_garden,
            cards::meditations_on_the_tao,
            cards::pilgrimage,

            // dynasty
            cards::akodo_gunso,
            cards::akodo_toturi,
            cards::deathseeker,
            cards::honored_general,
            cards::ikoma_eiji,
            cards::ikoma_prodigy,
            cards::kitsu_spiritcaller,
            cards::lions_pride_brawler,
            cards::matsu_beiona,
            cards::matsu_berserker,
            cards::obstinate_recruit,
            cards::staging_ground,
            cards::steadfast_samurai,
            cards::venerable_historian,
            cards::seppun_guardsman,
            cards::wandering_ronin,
            cards::favorable_ground,
            cards::imperial_storehouse,
            cards::otomo_courtier,
            cards::otomo_courtier,
            cards::miya_mystic,
            cards::miya_mystic,

            // conflict
            cards::for_greater_glory,
            cards::guidance_of_the_ancestors,
            cards::honored_blade,
            cards::master_of_the_spear,
            cards::ready_for_battle,
            cards::sashimono,
            cards::stand_your_ground,
            cards::strength_in_numbers,
            cards::vengeful_oathkeeper,
            cards::way_of_the_lion,
            cards::assassination,
            cards::banzai,
            cards::charge,
            cards::contingency_plan,
            cards::court_games,
            cards::fallen_in_battle,
            cards::for_shame,
            cards::good_omen,
            cards::outwit,
            cards::rout,
            cards::spies_at_court,
            cards::fine_katana,
            cards::ornate_fan,
            cards::cloud_the_mind
         }
      },
      {"Crane Starter Deck",
         {
            // stronghold
            cards::shizuka_toshi,

            // provinces
            cards::the_art_of_peace,
            cards::entrenched_position,
            cards::night_raid,
            cards::rally_to_the_cause,
            cards::shameful_display,

            // dynasty
            cards::asahina_artisan,
            cards::asahina_storyteller,
            cards::brash_samurai,
            cards::cautious_scout,
            cards::daidoji_nerishma,
            cards::doji_challenger,
            cards::doji_gift_giver,
            cards::doji_hotaru,
            cards::doji_whisperer,
            cards::guest_of_honor,
            cards::kakita_asami,
            cards::kakita_kaezin,
            cards::savvy_politician,
            cards::artisan_academy,
            cards::otomo_courtier,
            cards::miya_mystic,
            cards::favorable_ground,
            cards::imperial_storehouse,
            cards::seppun_guardsman,
            cards::seppun_guardsman,
            cards::wandering_ronin,
            cards::wandering_ronin,

            // conflict
            cards::above_question,
            cards::duelist_training,
            cards::height_of_fashion,
            cards::steward_of_law,
            cards::admit_defeat,
            cards::noble_sacrifice,
            cards::the_perfect_gift,
            cards::voice_of_honor,
            cards::way_of_the_crane,
            cards::political_rival,
            cards::assassination,
            cards::banzai,
            cards::charge,
            cards::contingency_plan,
            cards::court_games,
            cards::fallen_in_battle,
            cards::for_shame,
            cards::good_omen,
            cards::outwit,
            cards::rout,
            cards::spies_at_court,
            cards::fine_katana,
            cards::ornate_fan,
            cards::cloud_the_mind
         }
      }
   };
};
