#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "deckreshuffle.h"
#include "decision.h"
#include "choicesimulation.h"
#include <algorithm>
#include <fstream>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( DeckReshuffle );

void DeckReshuffle::setUp()
{
   std::unique_ptr<agent> lion = std::make_unique<humanagent>("testplayer1", decklists[0]);
   std::unique_ptr<agent> crane = std::make_unique<humanagent>("testplayer2", decklists[1]);

   gameEngine = new engine(std::move(lion), std::move(crane)); 
}

void DeckReshuffle::tearDown()
{
   delete gameEngine;
}

void DeckReshuffle::testDynastyReshuffle()
{
   std::list<choice> cl = {{"Ancestral Lands", choicetype::card}, // player1 plays pilgrimage
                           {"The Art of Peace", choicetype::card},
                           {"Akodo Toturi", choicetype::card},
                           {"Deathseeker", choicetype::card},
                           {"Honored General", choicetype::card},
                           {"Pass", choicetype::pass},
                           {"Brash Samurai", choicetype::card},
                           {"Pass", choicetype::pass},
                           {"Master of the Spear", choicetype::card},
                           {"Pass", choicetype::pass},
                           {"Above Question", choicetype::card},
                           {"Steward of Law", choicetype::card},
                           {"Duelist Training", choicetype::card},
                           {"Height of Fashion", choicetype::card},
                           {"Akodo Gunso", choicetype::card},
                           {"0 fate", choicetype::fate},
                           {"Asahina Storyteller", choicetype::card},
                           {"2 fate", choicetype::fate},
                           {"Ikoma Eiji", choicetype::card},
                           {"0 fate", choicetype::fate},
                           {"Asahina Artisan", choicetype::card},
                           {"0 fate", choicetype::fate},
                           {"Ikoma Prodigy", choicetype::card},
                           {"0 fate", choicetype::fate},
                           {"Pass", choicetype::pass},
                           {"Pass", choicetype::pass},
                           {"1", choicetype::bid},
                           {"4", choicetype::bid}}; // player2 plays rally

   choiceSimulation(cl, gameEngine);

   gamestate gs = gameEngine->getGameState();

   // output gamestate
   boost::archive::text_oarchive oa(std::cout);
   oa << gs;
}


