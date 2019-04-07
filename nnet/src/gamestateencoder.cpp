#include "gamestateencoder.h"
#include "characterslot.h"
#include "holdingslot.h"
#include "provinceslot.h"
#include "gamestatebuilder.h"
#include "state/gamestate.h"
#include "state/province.h"
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
   // TODO: check size
   if(size != builder->getTotalSize())
   {
      std::cout << "Size does not match GamestateBuilder size" << std::endl;
      return;
   }

   // look for characters in deck
   for(auto c : state->player1State.cards.dynastyDeck)
   {
      encodeDeckCard(c);
   }

   for(auto c : state->player2State.cards.dynastyDeck)
   {
      encodeDeckCard(c);
   }

   // look through provinces
   int provNum=1;
   for(auto p : state->player1State.cards.provinceArea)
   {
      encodeProvinceCard(provNum, p.dynastyCard, p.provinceCard, p.facedownDynasty,
         (p.provinceStatus == provinceCardStatus::broken), // broken
         (p.provinceCard == state->conflict_state.contested_province), // contested
         (p.provinceCard == state->player1State.cards.strongholdProvince || p.provinceCard == state->player2State.cards.strongholdProvince)); // stronghold
      provNum++;
   }

   provNum=1;
   for(auto p : state->player2State.cards.provinceArea)
   {
      encodeProvinceCard(provNum, p.dynastyCard, p.provinceCard, p.facedownDynasty,
         (p.provinceStatus == provinceCardStatus::broken), // broken
         (p.provinceCard == state->conflict_state.contested_province), // contested
         (p.provinceCard == state->player1State.cards.strongholdProvince || p.provinceCard == state->player2State.cards.strongholdProvince)); // stronghold
      provNum++;
   }

   // look for characters in play
   for(auto ch : state->player1State.cards.atHome)
   {
      encodeCharacter(ch.characterCard, true, ch.bowed, ch.fateAttached);
   }

   for(auto ch : state->player2State.cards.atHome)
   {
      encodeCharacter(ch.characterCard, true, ch.bowed, ch.fateAttached);
   }

   // look for conflict characters
   for(auto ch : state->player1State.conflict_state.inConflict)
   {
      encodeCharacter(ch.characterCard, false, ch.bowed, ch.fateAttached);
   }

   for(auto ch : state->player2State.conflict_state.inConflict)
   {
      encodeCharacter(ch.characterCard, false, ch.bowed, ch.fateAttached);
   }

   // pending fate characters
   encodeCharacter(state->player1State.cards.pendingFateCard, false, false, 0);

   encodeCharacter(state->player2State.cards.pendingFateCard, false, false, 0);
}

void GamestateEncoder::encodeDeckCard(int card)
{
   // check character
   auto charOffset = characterMap.find(card);
   if(charOffset != characterMap.end())
   {
      CharacterSlot *cs = builder->getCharacter(charOffset->second);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->in_deck = 1.0;
   }
   // check holding
   auto holdingOffset = holdingMap.find(card);
   if(holdingOffset != holdingMap.end())
   {
      HoldingSlot *hs = builder->getHolding(holdingOffset->second);
      memset(hs, 0, sizeof(HoldingSlot));
      hs->in_deck = 1.0;
   }
   if(charOffset != characterMap.end() && (holdingOffset != holdingMap.end()))
   {
      std::cout << "Card " << card << "  matched both a character and holding" << std::endl;
   }
   else if(charOffset == characterMap.end() && (holdingOffset == holdingMap.end()))
   {
      std::cout << "Card " << card << " didn't match either a character or holding" << std::endl;
   }
}

// TODO: Add revealed bool
void GamestateEncoder::encodeProvinceCard(int provNum, int dynastyCard, int provinceCard, bool facedownDynasty, bool broken, bool contested, bool stronghold)
{
   // encode the dynasty card
   auto charOffset = characterMap.find(dynastyCard);
   if(charOffset != characterMap.end())
   {
      CharacterSlot *cs = builder->getCharacter(charOffset->second);
      memset(cs, 0, sizeof(CharacterSlot));
      switch(provNum)
      {
         case 1:
            cs->province1 = 1.0;
            break;
         case 2:
            cs->province2 = 1.0;
            break;
         case 3:
            cs->province3 = 1.0;
            break;
         case 4:
            cs->province4 = 1.0;
            break;
         default:
            std::cout << "Invalid province number" << std::endl;
            break;
      }
      if(!facedownDynasty)
      {
         cs->revealed = 1.0;
      }
   }

   auto holdingOffset = holdingMap.find(dynastyCard);
   if(holdingOffset != holdingMap.end())
   {
      HoldingSlot *hs = builder->getHolding(holdingOffset->second);
      memset(hs, 0, sizeof(HoldingSlot));
      switch(provNum)
      {
         case 1:
            hs->province1 = 1.0;
            break;
         case 2:
            hs->province2 = 1.0;
            break;
         case 3:
            hs->province3 = 1.0;
            break;
         case 4:
            hs->province4 = 1.0;
            break;
         default:
            std::cout << "Invalid province number" << std::endl;
            break;
      }
      if(!facedownDynasty)
      {
         hs->revealed = 1.0;
      }
   }
   else
   {
      std::cout << "Province dynasty card didn't match character or holding" << std::endl;
   }

   // match actual province
   auto pm = provinceMap.find(provinceCard);
   if(pm != provinceMap.end())
   {
      ProvinceSlot *ps = builder->getProvince(pm->second);
      memset(ps, 0, sizeof(ProvinceSlot));
      switch(provNum)
      {
         case 1:
            ps->province1 = 1.0;
            break;
         case 2:
            ps->province2 = 1.0;
            break;
         case 3:
            ps->province3 = 1.0;
            break;
         case 4:
            ps->province4 = 1.0;
            break;
         default:
            //std::cout << "Invalid province number" << std::endl;
            // Early in the game you can have 5 provinces before you pick your stronghold province
            // for now just set nothing
            break;
      }
      if(broken)
      {
         ps->broken = 1.0;
      }
      // check contested
      if(contested)
      {
         ps->contested = 1.0;
      }
      // check stronghold
      if(stronghold)
      {
         ps->stronghold = 1.0;
      }
   }
   else
   {
      std::cout << "Province card not found!" << std::endl;
   }
}

void GamestateEncoder::encodeCharacter(int characterCard, bool atHome, bool bowed, int fateAttached)
{
   auto charOffset = characterMap.find(characterCard);
   if(charOffset != characterMap.end())
   {
      CharacterSlot *cs = builder->getCharacter(charOffset->second);
      memset(cs, 0, sizeof(CharacterSlot));
      if(atHome)
      {
         cs->at_home = 1.0;
      }
      if(bowed)
      {
         cs->bowed = 1.0;
      }
      if(fateAttached > 10)
      {
         std::cout << "WARNING: More than 10 fate on a character" << std::endl;
      }
      else
      {
         cs->storedFate[fateAttached] = 1.0;
      }
   }
   else
   {
      std::cout << "Character card not found in character map!" << std::endl;
   }
}
