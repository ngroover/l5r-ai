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

   // look for characters in deck
   for(auto c : state->player1State.cards.dynastyDeck)
   {
      int charOffset=characterMap[c];
      CharacterSlot *cs = builder->getCharacter(charOffset);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->in_deck = 1.0;
   }

   for(auto c : state->player2State.cards.dynastyDeck)
   {
      int charOffset=characterMap[c];
      CharacterSlot *cs = builder->getCharacter(charOffset);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->in_deck = 1.0;
   }

   // look for characters in provinces
   int provNum=1;
   for(auto p : state->player1State.cards.provinceArea)
   {
      auto cm = characterMap.find(p.dynastyCard);
      if(cm != characterMap.end())
      {
         int charOffset=characterMap[p.dynastyCard];
         CharacterSlot *cs = builder->getCharacter(charOffset);
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
               cs->province3 = 1.0;
               break;
            default:
               std::cout << "Invalid province number" << std::endl;
               break;
         }
         if(!p.facedownDynasty)
         {
            cs->revealed = 1.0;
         }
      }
      provNum++;
   }

   provNum=1;
   for(auto p : state->player2State.cards.provinceArea)
   {
      auto cm = characterMap.find(p.dynastyCard);
      if(cm != characterMap.end())
      {
         int charOffset=characterMap[p.dynastyCard];
         CharacterSlot *cs = builder->getCharacter(charOffset);
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
               cs->province3 = 1.0;
               break;
            default:
               std::cout << "Invalid province number" << std::endl;
               break;
         }
         if(!p.facedownDynasty)
         {
            cs->revealed = 1.0;
         }
      }
      provNum++;
   }

   // look for characters in play
   for(auto ch : state->player1State.cards.atHome)
   {
      int charOffset=characterMap[ch.characterCard];
      CharacterSlot *cs = builder->getCharacter(charOffset);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->at_home = 1.0;
      if(ch.bowed)
      {
         cs->bowed = 1.0;
      }
      if(ch.fateAttached > 10)
      {
         std::cout << "WARNING: More than 10 fate on a character" << std::endl;
      }
      else
      {
         cs->storedFate[ch.fateAttached] = 1.0;
      }
   }

   for(auto ch : state->player2State.cards.atHome)
   {
      int charOffset=characterMap[ch.characterCard];
      CharacterSlot *cs = builder->getCharacter(charOffset);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->at_home = 1.0;
      if(ch.bowed)
      {
         cs->bowed = 1.0;
      }
      if(ch.fateAttached > 10)
      {
         std::cout << "WARNING: More than 10 fate on a character" << std::endl;
      }
      else
      {
         cs->storedFate[ch.fateAttached] = 1.0;
      }
   }

   // look for conflict characters
   for(auto ch : state->player1State.conflict_state.inConflict)
   {
      int charOffset=characterMap[ch.characterCard];
      CharacterSlot *cs = builder->getCharacter(charOffset);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->at_home = 1.0;
      if(ch.bowed)
      {
         cs->bowed = 1.0;
      }
      if(ch.fateAttached > 10)
      {
         std::cout << "WARNING: More than 10 fate on a character" << std::endl;
      }
      else
      {
         cs->storedFate[ch.fateAttached] = 1.0;
      }
   }

   for(auto ch : state->player2State.conflict_state.inConflict)
   {
      int charOffset=characterMap[ch.characterCard];
      CharacterSlot *cs = builder->getCharacter(charOffset);
      memset(cs, 0, sizeof(CharacterSlot));
      cs->at_home = 1.0;
      if(ch.bowed)
      {
         cs->bowed = 1.0;
      }
      if(ch.fateAttached > 10)
      {
         std::cout << "WARNING: More than 10 fate on a character" << std::endl;
      }
      else
      {
         cs->storedFate[ch.fateAttached] = 1.0;
      }
   }

   // TODO: look at pending fate character

   // encode holdings
   for(auto h : state->player1State.cards.dynastyDeck)
   {
      int holdingOffset=holdingMap[h];
      HoldingSlot *hs = builder->getHolding(holdingOffset);
      memset(hs, 0, sizeof(HoldingSlot));
      //hs->in_deck = 1.0;
   }

   for(auto h : state->player2State.cards.dynastyDeck)
   {
      int holdingOffset=holdingMap[h];
      HoldingSlot *hs = builder->getHolding(holdingOffset);
      memset(hs, 0, sizeof(HoldingSlot));
      //hs->in_deck = 1.0;
   }

   // encode provinces
   provNum=1;
   for(auto p : state->player1State.cards.provinceArea)
   {
      auto pm = provinceMap.find(p.provinceCard);
      if(pm != provinceMap.end())
      {
         int provOffset=provinceMap[p.provinceCard];
         ProvinceSlot *ps = builder->getProvince(provOffset);
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
               ps->province3 = 1.0;
               break;
            default:
               std::cout << "Invalid province number" << std::endl;
               break;
         }
         if(p.provinceStatus == provinceCardStatus::broken)
         {
            ps->broken = 1.0;
         }
      }
      provNum++;
   }

   provNum=1;
   for(auto p : state->player2State.cards.provinceArea)
   {
      auto pm = provinceMap.find(p.provinceCard);
      if(pm != provinceMap.end())
      {
         int provOffset=provinceMap[p.provinceCard];
         ProvinceSlot *ps = builder->getProvince(provOffset);
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
               ps->province3 = 1.0;
               break;
            default:
               std::cout << "Invalid province number" << std::endl;
               break;
         }
         if(p.provinceStatus == provinceCardStatus::broken)
         {
            ps->broken = 1.0;
         }
      }
      provNum++;
   }

   // strongholds
   {
      auto pm = provinceMap.find(state->player1State.cards.strongholdProvince);
      if(pm != provinceMap.end())
      {
         int provOffset=provinceMap[state->player1State.cards.strongholdProvince];
         ProvinceSlot *ps = builder->getProvince(provOffset);
         memset(ps, 0, sizeof(ProvinceSlot));
         ps->stronghold = 1.0;
      }
   }

   {
      auto pm = provinceMap.find(state->player2State.cards.strongholdProvince);
      if(pm != provinceMap.end())
      {
         int provOffset=provinceMap[state->player2State.cards.strongholdProvince];
         ProvinceSlot *ps = builder->getProvince(provOffset);
         memset(ps, 0, sizeof(ProvinceSlot));
         ps->stronghold = 1.0;
      }
   }

   // contested province
   {
      auto pm = provinceMap.find(state->conflict_state.contested_province);
      if(pm != provinceMap.end())
      {
         int provOffset=provinceMap[state->conflict_state.contested_province];
         ProvinceSlot *ps = builder->getProvince(provOffset);
         memset(ps, 0, sizeof(ProvinceSlot));
         ps->contested = 1.0;
      }
   }
}

void GamestateEncoder::encodeCardStates(gamestate *state, double *networkInput)
{
}


