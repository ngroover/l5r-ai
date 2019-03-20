#include "gamestateencoder.h"
#include "charactercardslot.h"
#include "gamestatebuilder.h"
#include "state/gamestate.h"
#include <iostream>

using namespace l5r;

GamestateEncoder::GamestateEncoder()
{
   builder = NULL;
}

GamestateEncoder::~GamestateEncoder()
{
   if(builder != NULL)
   {
      delete builder;
   }
}

void GamestateEncoder::setupMap(gamestate *state)
{
   // TODO: integrate with carddatamanager to figure out which cards are characters
   int i=0;
   int charIndex=0; // character index
   int holdingIndex=0; // holding index
   int provinceIndex=0; // province index
   for(auto c : state->cardIds)
   {
      // characters....this is really bad hack but temporary
         // crane
      if(checkIfCharacter(c))
      {
         characterMap.insert(std::pair<int,int>(i, charIndex++));
      }
      if(checkIfHolding(c))
      {
         holdingMap.insert(std::pair<int,int>(i, holdingIndex++));
      }
      if(checkIfProvince(c))
      {
         provinceMap.insert(std::pair<int,int>(i, provinceIndex++));
      }
      i++;
   }
   std::cout << "character map is " << characterMap.size() << " big" << std::endl;
   std::cout << "holding map is " << holdingMap.size() << " big" << std::endl;
   std::cout << "province map is " << provinceMap.size() << " big" << std::endl;

   // create builder
   builder = new GamestateBuilder(characterMap.size(), holdingMap.size(), provinceMap.size());
}

bool GamestateEncoder::checkIfCharacter(cards c)
{
      return (c == cards::asahina_artisan
         || c == cards::asahina_storyteller
         || c == cards::brash_samurai
         || c == cards::cautious_scout
         || c == cards::daidoji_nerishma
         || c == cards::doji_challenger
         || c == cards::doji_gift_giver
         || c == cards::doji_hotaru
         || c == cards::doji_whisperer
         || c == cards::guest_of_honor
         || c == cards::kakita_asami
         || c == cards::kakita_kaezin
         || c == cards::savvy_politician
         // neutral
         || c == cards::otomo_courtier
         || c == cards::miya_mystic
         || c == cards::seppun_guardsman
         || c == cards::wandering_ronin
         || c == cards::obstinate_recruit
         // lion
         || c == cards::akodo_gunso
         || c == cards::akodo_toturi
         || c == cards::deathseeker
         || c == cards::honored_general
         || c == cards::ikoma_eiji
         || c == cards::ikoma_prodigy
         || c == cards::kitsu_spiritcaller
         || c == cards::lions_pride_brawler
         || c == cards::matsu_beiona
         || c == cards::matsu_berserker
         || c == cards::steadfast_samurai
         || c == cards::venerable_historian);
}

bool GamestateEncoder::checkIfHolding(cards c)
{
   if(c == cards::staging_ground ||
      c == cards::artisan_academy ||
      c == cards::favorable_ground ||
      c == cards::imperial_storehouse);
}

bool GamestateEncoder::checkIfProvince(cards c)
{
   if(c == cards::the_art_of_peace ||
      c == cards::entrenched_position ||
      c == cards::night_raid ||
      c == cards::rally_to_the_cause ||
      c == cards::shameful_display ||
      c == cards::the_art_of_war ||
      c == cards::ancestral_lands ||
      c == cards::manicured_gardens ||
      c == cards::meditations_on_the_tao ||
      c == cards::pilgrimage);
}

int GamestateEncoder::getTotalSize()
{
   return builder->getTotalSize();
}

void GamestateEncoder::encode(gamestate *state, double *networkInput, int size)
{
   encodeCardStates(state, networkInput);
}

void GamestateEncoder::encodeCardStates(gamestate *state, double *networkInput)
{
}


