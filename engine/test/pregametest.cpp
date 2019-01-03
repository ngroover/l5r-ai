#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "pregametest.h"
#include "decision.h"
#include "choicesimulation.h"
#include <algorithm>
#include <fstream>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( PregameTest );

void PregameTest::setUp()
{
   std::unique_ptr<agent> lion = std::make_unique<humanagent>("testplayer1", decklists[0]);
   std::unique_ptr<agent> crane = std::make_unique<humanagent>("testplayer2", decklists[1]);

   gameEngine = new engine(std::move(lion), std::move(crane)); 
}

void PregameTest::tearDown()
{
   delete gameEngine;
}

void PregameTest::testStrongholdDecision()
{
   std::list<choice> cl = {{"Pilgrimage", choicetype::card}, // player1 plays pilgrimage
                           {"Rally to the Cause", choicetype::card}}; // player2 plays rally

   choiceSimulation(cl, gameEngine);

   gamestate gs = gameEngine->getGameState();

   // output gamestate
   //boost::archive::text_oarchive oa(std::cout);
   //oa << gs;
}

void PregameTest::testNoMulligans()
{
   std::string serialized = "22 serialization::archive 14 0 1 0 0 104 0 32 33 34 35 36 37 38 39 40 41 42 43 44 45 30 31 28 29 26 26 27 27 70 71 72 73 74 75 76 77 78 79 56 57 58 59 60 61 62 63 64 65 66 67 68 69 1 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 30 31 31 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 0 2 3 4 5 6 0 1 0 0 0 0 0 0 18 0 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 0 0 24 0 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 0 0 0 0 0 0 0 4 0 0 0 47 0 1 0 48 1 1 0 49 2 1 0 50 3 1 0 51 46 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 18 0 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 0 0 24 0 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 0 0 0 0 0 4 0 99 52 1 0 100 53 1 0 101 54 1 0 103 55 1 0 102 98 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";

   std::stringstream ss;
   ss << serialized;
   gamestate gs;
   boost::archive::text_iarchive ia(ss);
   ia >> gs;

   gameEngine->setGameState(gs);

   std::list<choice> cl = {{"Pass", choicetype::pass}, // player1 passes dynasty mulligan
                           {"Pass", choicetype::pass}, // player2 passes dynasty mulligan
                           {"Pass", choicetype::pass}, // player1 passes conflict mulligan
                           {"Pass", choicetype::pass}}; // player2 passes conflict mulligan

   choiceSimulation(cl, gameEngine);

   gs = gameEngine->getGameState();

   // output gamestate
   //boost::archive::text_oarchive oa(std::cout);
   //oa << gs;
}


