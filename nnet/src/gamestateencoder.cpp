#include "gamestateencoder.h"
#include "charactercardslot.h"
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
      if(checkIfCharacter(c))
      {
         characterMap.insert(std::pair<int,int>(i, charIndex++));
      }
      i++;
   }
   std::cout << "map is " << characterMap.size() << " big" << std::endl;
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

void GamestateEncoder::encode(gamestate *state, double *networkInput, int size)
{
/*
   if(size != state_input_size)
   {
      std::cout << "size does not match expected input size" << std::endl;  
      return;
   }
   */

   int characterSize = encodeCardStates(state, networkInput);
   std::cout << "Character size=" << characterSize << std::endl;
}

int GamestateEncoder::encodeCardStates(gamestate *state, double *networkInput)
{
   CharacterCardSlot converter;
   const int totalSize = characterMap.size() * converter.getSize();
   bool foundCard[characterMap.size()] ={false};

   // characters are in deck
   converter.setState(CharacterSlotStatus::in_deck);

   // set all the character slots
   // player1 deck
   for(auto c : state->player1State.cards.dynastyDeck)
   {
      if(checkIfCharacter(state->cardIds[c]))
      {
         int networkOffset = characterMap[c]*converter.getSize();
         if(foundCard[characterMap[c]])
         {
            std::cout << "Error found card already above " << characterMap[c] << std::endl;
         }
         foundCard[characterMap[c]] = true;
         converter.setOutput(&networkInput[networkOffset]);
      }
   }

   // player2 deck
   for(auto c : state->player2State.cards.dynastyDeck)
   {
      if(checkIfCharacter(state->cardIds[c]))
      {
         int networkOffset = characterMap[c]*converter.getSize();
         if(foundCard[characterMap[c]])
         {
            std::cout << "Error found card already above " << characterMap[c] << std::endl;
         }
         foundCard[characterMap[c]] = true;
         converter.setOutput(&networkInput[networkOffset]);
      }
   }

   int i=0;
   std::cout << "provinces" << std::endl;
   // player1 provinces
   for(auto c : state->player1State.cards.provinceArea)
   {
      switch(i++)
      {
      case 0:
         converter.setState(CharacterSlotStatus::province1);
         break;
      case 1:
         converter.setState(CharacterSlotStatus::province2);
         break;
      case 2:
         converter.setState(CharacterSlotStatus::province3);
         break;
      case 3:
         converter.setState(CharacterSlotStatus::province4);
         break;
      }
      // check dynasty card is actually a character.  See hack above
      if(c.dynastyCard >= 0)
      {
         if(checkIfCharacter(state->cardIds[c.dynastyCard]))
         {
            int networkOffset = characterMap[c.dynastyCard]*converter.getSize();
            if(foundCard[characterMap[c.dynastyCard]])
            {
               std::cout << "Error found card already above " << characterMap[c.dynastyCard] << std::endl;
            }
            foundCard[characterMap[c.dynastyCard]] = true;
            converter.setOutput(&networkInput[networkOffset]);
         }
      }
   }

   // player2 provinces
   for(auto c : state->player2State.cards.provinceArea)
   {
      switch(i++)
      {
      case 0:
         converter.setState(CharacterSlotStatus::province1);
         break;
      case 1:
         converter.setState(CharacterSlotStatus::province2);
         break;
      case 2:
         converter.setState(CharacterSlotStatus::province3);
         break;
      case 3:
         converter.setState(CharacterSlotStatus::province4);
         break;
      }
      // check dynasty card is actually a character.  See hack above
      if(c.dynastyCard >= 0)
      {
         if(checkIfCharacter(state->cardIds[c.dynastyCard]))
         {
            int networkOffset = characterMap[c.dynastyCard]*converter.getSize();
            if(foundCard[characterMap[c.dynastyCard]])
            {
               std::cout << "Error found card already above " << characterMap[c.dynastyCard] << std::endl;
            }
            foundCard[characterMap[c.dynastyCard]] = true;
            converter.setOutput(&networkInput[networkOffset]);
         }
      }
   }

   for(int i=0;i < characterMap.size(); i++)
   {
      if(!foundCard[i])
      {
         std::cout << "Didn't find card" << i <<  std::endl;
      }
   }
   std::cout << "Done" << std::endl;

   return totalSize;
}


