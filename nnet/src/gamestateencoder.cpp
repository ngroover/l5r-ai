#include "gamestateencoder.h"
#include "characterslot.h"
#include "holdingslot.h"
#include "provinceslot.h"
#include "gamestatebuilder.h"
#include "state/gamestate.h"
#include <iostream>
#include <cstring>

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
   return (c == cards::staging_ground ||
      c == cards::artisan_academy ||
      c == cards::favorable_ground ||
      c == cards::imperial_storehouse);
}

bool GamestateEncoder::checkIfProvince(cards c)
{
   return (c == cards::the_art_of_peace ||
      c == cards::entrenched_position ||
      c == cards::night_raid ||
      c == cards::rally_to_the_cause ||
      c == cards::shameful_display ||
      c == cards::the_art_of_war ||
      c == cards::ancestral_lands ||
      c == cards::manicured_garden ||
      c == cards::meditations_on_the_tao ||
      c == cards::pilgrimage);
}

int GamestateEncoder::getTotalSize()
{
   return builder->getTotalSize();
}

void GamestateEncoder::encode(gamestate *state, double *networkInput, int size)
{
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
      encodeProvinceCard(provNum, p->dynastyCard, p->provinceCard, p->facedownDynasty,
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
      encodeCharacter(ch.characterCard, true, ch.bowed, ch.fateAttached, false, false);
   }

   for(auto ch : state->player2State.cards.atHome)
   {
      encodeCharacter(ch.characterCard, true, ch.bowed, ch.fateAttached, false, false);
   }

   // look for conflict characters
   for(auto ch : state->player1State.conflict_state.inConflict)
   {
      encodeCharacter(ch.characterCard, false, ch.bowed, ch.fateAttached, false, false);
   }

   for(auto ch : state->player2State.conflict_state.inConflict)
   {
      encodeCharacter(ch.characterCard, false, ch.bowed, ch.fateAttached, false, false);
   }

   // look at mulligan characters
   for(auto ch : state->player1State.cards.pendingMulligan)
   {
      encodeCharacter(ch, false, false, false, false, true);
   }

   for(auto ch : state->player2State.cards.pendingMulligan)
   {
      encodeCharacter(ch, false, false, false, false, true);
   }
   

   // look at pending fate characters
   if(state->player1State.cards.pendingFateCard != -1)
   {
      encodeCharacter(state->player1State.cards.pendingFateCard, false, false, 0, true, false);
   }

   if(state->player2State.cards.pendingFateCard != -1)
   {
      encodeCharacter(state->player2State.cards.pendingFateCard, false, false, 0, true, false);
   }

   // rings
   // hopefully theres always 5 rings
   for(int r=0;r < 5; r++)
   {
      ring ringType;
      switch(r)
      {
         case 0:
            ringType=ring::air;
            break;
         case 1:
            ringType=ring::fire;
            break;
         case 2:
            ringType=ring::earth;
            break;
         case 3:
            ringType=ring::water;
            break;
         case 4:
            ringType=ring::_void;
            break;
         default:
            std::cout << "Unknown ring" << std::endl;
            break;
      }
      bool claimed=false;
      int player=0;
      for(auto tmpRing : state->player1State.conflict_state.claimed_rings)
      {
         if(tmpRing == ringType)
         {
            claimed = true;
            player=1;
         }
      }
      for(auto tmpRing : state->player2State.conflict_state.claimed_rings)
      {
         if(tmpRing == ringType)
         {
            if(claimed)
            {
               std::cout << "Ring shouldn't be claimed by both players" << std::endl;
            }
            claimed = true;
            player=2;
         }
      }
      bool contested = (ringType == state->conflict_state.contested_ring);

      RingSlot *rs = builder->getRing(r);
      memset(rs, 0, sizeof(RingSlot));
      if(claimed)
      {
         switch(player)
         {
            case 1:
               rs->player1_claimed = 1.0;
               break;
            case 2:
               rs->player2_claimed = 1.0;
               break;
            default:
               std::cout << "Player not set" << std::endl;
               break;
         }
      }
      else
      {
         rs->unclaimed = 1.0;
      }
      if(contested)
      {
         rs->contested = 1.0;
      }
   }

   // encode player data
   PlayerSlot *ps = builder->getPlayer(0);
   memset(ps, 0, sizeof(PlayerSlot));
   if(state->player1State.tokens.honorTokens >= 0 &&
         state->player1State.tokens.honorTokens < 25)
   {
      ps->honor[state->player1State.tokens.honorTokens] = 1.0;
   }
   else
   {
      std::cout << "Invalid honor tokens" << std::endl;
   }
   if(state->player1State.tokens.fate >= 50)
   {
      std::cout << "Player 1 Fate >= 50.  Cannot support." << std::endl;
      ps->fate[49] = 1.0;
   }
   else
   {
      ps->fate[state->player1State.tokens.fate] = 1.0;
   }
   if(state->player1State.tokens.honorDial >= 0 && state->player1State.tokens.honorDial <=6)
   {
      ps->honorDial[state->player1State.tokens.honorDial] = 1.0;
   }
   if(state->player1State.conflict_state.militaryConflictsLeft < 2)
   {
      ps->mil_left[state->player1State.conflict_state.militaryConflictsLeft] = 1.0;
   }
   if(state->player1State.conflict_state.politicalConflictsLeft < 2)
   {
      ps->pol_left[state->player1State.conflict_state.politicalConflictsLeft] = 1.0;
   }
   if(state->player1State.conflict_state.totalConflictsLeft < 2)
   {
      ps->conflicts_left[state->player1State.conflict_state.totalConflictsLeft] = 1.0;
   }

   if(state->player1State.conflict_state.hasImperialFavor)
   {
      ps->hasFavor = 1.0;
   }

   ps = builder->getPlayer(1);
   memset(ps, 0, sizeof(PlayerSlot));
   if(state->player2State.tokens.honorTokens >= 0 &&
         state->player2State.tokens.honorTokens < 25)
   {
      ps->honor[state->player2State.tokens.honorTokens] = 1.0;
   }
   else
   {
      std::cout << "Invalid honor tokens" << std::endl;
   }
   if(state->player2State.tokens.fate >= 50)
   {
      std::cout << "Player 2 Fate >= 50.  Cannot support." << std::endl;
      ps->fate[49] = 1.0;
   }
   else
   {
      ps->fate[state->player2State.tokens.fate] = 1.0;
   }
   if(state->player2State.tokens.honorDial >= 0 && state->player2State.tokens.honorDial <=6)
   {
      ps->honorDial[state->player2State.tokens.honorDial] = 1.0;
   }
   if(state->player2State.conflict_state.militaryConflictsLeft >= 0 && state->player2State.conflict_state.militaryConflictsLeft < 2)
   {
      ps->mil_left[state->player2State.conflict_state.militaryConflictsLeft] = 1.0;
   }
   if(state->player2State.conflict_state.politicalConflictsLeft >= 0 && state->player2State.conflict_state.politicalConflictsLeft < 2)
   {
      ps->pol_left[state->player2State.conflict_state.politicalConflictsLeft] = 1.0;
   }
   if(state->player2State.conflict_state.totalConflictsLeft >= 0 && state->player2State.conflict_state.totalConflictsLeft < 2)
   {
      ps->conflicts_left[state->player2State.conflict_state.totalConflictsLeft] = 1.0;
   }

   if(state->player2State.conflict_state.hasImperialFavor)
   {
      ps->hasFavor = 1.0;
   }
   
   // encode global data
   GlobalSlot *gs = builder->getGlobal();
   memset(gs, 0, sizeof(GlobalSlot));
   switch(state->currentPhase)
   {
      case phase::pregame:
         gs->pregame = 1.0;
         break;
      case phase::dynasty:
         gs->dynasty = 1.0;
         break;
      case phase::draw:
         gs->draw = 1.0;
         break;
      case phase::conflict:
         gs->conflict = 1.0;
         break;
      case phase::fate:
         gs->fate = 1.0;
         break;
      case phase::regroup:
         gs->regroup = 1.0;
         break;
      case phase::gameover:
         std::cout << "Shouldn't be getting game over state" << std::endl;
         break;
      default:
         std::cout << "Encoding unknown state" << std::endl;
   }
   switch(state->currentSubPhase)
   {
      case subphase::stronghold_selection:
         gs->stronghold_selection = 1.0;
         break;
      case subphase::dynasty_mulligan:
         gs->dynasty_mulligan = 1.0;
         break;
      case subphase::conflict_mulligan:
         gs->conflict_mulligan = 1.0;
         break;
      case subphase::dynasty_setup:
         gs->dynasty_setup = 1.0;
         break;
      case subphase::province_play:
         gs->province_play = 1.0;
         break;
      case subphase::additional_fate:
         gs->additional_fate = 1.0;
         break;
      case subphase::bid:
         gs->bid = 1.0;
         break;
      case subphase::choose_attackers:
         gs->choose_attackers = 1.0;
         break;
      case subphase::choose_ring:
         gs->choose_ring = 1.0;
         break;
      case subphase::choose_conflicttype:
         gs->choose_conflicttype = 1.0;
         break;
      case subphase::choose_defenders:
         gs->choose_defenders = 1.0;
         break;
      case subphase::conflict_action:
         gs->conflict_action = 1.0;
         break;
      case subphase::choose_favor:
         gs->choose_favor = 1.0;
         break;
      case subphase::choose_discard:
         gs->choose_discard = 1.0;
         break;
      default:
         std::cout << "Encoding unknown substate" << std::endl;
   }

   if(state->currentTurn == player::player1)
   {
      gs->player1_turn = 1.0;
   }
   else
   {
      gs->player2_turn = 1.0;
   }
   if(state->currentConflict == player::player1)
   {
      gs->player1_conflict = 1.0;
   }
   else
   {
      gs->player2_conflict = 1.0;
   }
   if(state->currentAction == player::player1)
   {
      gs->player1_action = 1.0;
   }
   else
   {
      gs->player2_action = 1.0;
   }

   if(state->conflict_state.conflict_type == conflicttype::military)
   {
      gs->conflictMil = 1.0;
   }
   else
   {
      gs->conflictPol = 1.0;
   }
   if(state->conflict_state.favorType == conflicttype::military)
   {
      gs->favorMil = 1.0;
   }
   else
   {
      gs->favorPol = 1.0;
   }
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
   if((charOffset != characterMap.end()) && (holdingOffset != holdingMap.end()))
   {
      std::cout << "Card " << card << "  matched both a character and holding" << std::endl;
   }
   else if((charOffset == characterMap.end()) && (holdingOffset == holdingMap.end()))
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
            // this is normal
            //std::cout << "Invalid province number" << std::endl;
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
            // this is normal
            //std::cout << "Invalid province number" << std::endl;
            break;
      }
      if(!facedownDynasty)
      {
         hs->revealed = 1.0;
      }
   }
   else
   {
      // this is ok because sometimes provinces don't have a dynasty card
      //std::cout << "Province dynasty card didn't match character or holding" << std::endl;
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

void GamestateEncoder::encodeCharacter(int characterCard, bool atHome, bool bowed, int fateAttached, bool pendingFate, bool pendingMulligan)
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
      else
      {
         cs->in_conflict = 1.0;
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
      if(pendingFate)
      {
         cs->pending_fate = 1.0;
      }
      if(pendingMulligan)
      {
         cs->in_mulligan = 1.0;
      }
   }
   else
   {
      std::cout << "Character card not found in character map!" << std::endl;
   }
}

