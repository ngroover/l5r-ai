#include "gamestateencoder.h"
#include "state/gamestate.h"
#include <iostream>

using namespace l5r;

// TODO: dynamically generate
const int GamestateEncoder::state_input_size = 638;

GamestateEncoder::GamestateEncoder()
{
}

GamestateEncoder::~GamestateEncoder()
{
}

void GamestateEncoder::setupMap(gamestate *state)
{
   // TODO: integrate with carddatamanager to figure out which cards are characters
   int i=0;
   int charIndex=0; // character index
   for(auto c : state->cardIds)
   {
      // characters....this is really bad hack but temporary
         // crane
      if(c == cards::asahina_artisan
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
         || c == cards::venerable_historian)
      {
         characterMap.insert(std::pair<int,int>(i, charIndex++));
      }
      i++;
   }
}

void GamestateEncoder::encode(gamestate *state, double *networkInput, int size)
{
   if(size != state_input_size)
   {
      std::cout << "size does not match expected input size" << std::endl;  
      return;
   }

   int characterSize = encodeCardStates(state, networkInput);
   std::cout << "Character size=" << characterSize << std::endl;
}

int GamestateEncoder::encodeCardStates(gamestate *state, double *networkInput)
{
   CharacterCardSlot converter;
   const int totalSize = characterMap.size() * converter.getSize();

   // characters are in deck
   converter.setState(CharacterSlotStatus::in_deck);

   // set all the character slots
   for(auto c : state->player1State.cards.dynastyDeck)
   {
      int networkOffset = characterMap[c]*converter.getSize();
      converter.setOutput(&networkInput[networkOffset]);
   }

   return totalSize;
}


