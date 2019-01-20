#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "biddingtest.h"
#include "decision.h"
#include "choicesimulation.h"
#include <algorithm>
#include <fstream>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( BiddingTest );

void BiddingTest::setUp()
{
   std::unique_ptr<agent> lion = std::make_unique<humanagent>("testplayer1", decklists[0]);
   std::unique_ptr<agent> crane = std::make_unique<humanagent>("testplayer2", decklists[1]);

   gameEngine = new engine(std::move(lion), std::move(crane)); 

   std::string serialized = "22 serialization::archive 14 0 1 0 0 106 0 1 1 7 8 9 10 11 32 33 34 35 36 37 38 39 40 41 42 43 44 45 30 31 28 29 26 26 27 27 70 71 72 73 74 75 76 77 78 79 56 57 58 59 60 61 62 63 64 65 66 67 68 69 0 0 2 3 4 5 6 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 30 31 31 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 2 6 0 0 0 0 0 0 0 0 17 0 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 0 0 20 0 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 4 0 29 30 31 32 0 0 8 0 0 4 0 0 0 2 7 0 0 3 11 1 0 4 9 0 0 5 10 0 0 6 1 0 0 1 0 0 0 8 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 1 0 1 17 0 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 0 0 20 0 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 4 0 82 83 84 85 0 0 63 4 0 55 60 0 0 56 61 0 0 57 62 0 0 59 64 1 0 58 54 1 0 63 0 3 0 0 0 0 0 0 0 0 0 11 2 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 1 0 2 0 3 0 4 0 0";

   std::stringstream ss;
   ss << serialized;
   gamestate gs;
   boost::archive::text_iarchive ia(ss);
   ia >> gs;

   gameEngine->setGameState(gs);
}

void BiddingTest::tearDown()
{
   delete gameEngine;
}

void BiddingTest::tieAtFive()
{
   std::list<choice> cl = {{"5", choicetype::bid}, // player1 bid 5
                           {"5", choicetype::bid}}; // player2 bid 5

   choiceSimulation(cl, gameEngine);

   gamestate gs = gameEngine->getGameState();
   // output gamestate
   boost::archive::text_oarchive oa(std::cout);
   oa << gs;
}

void BiddingTest::tieAtOne()
{
   std::list<choice> cl = {{"1", choicetype::bid}, // player1 bid 1
                           {"1", choicetype::bid}}; // player2 bid 1

   choiceSimulation(cl, gameEngine);

   // output gamestate
   //boost::archive::text_oarchive oa(std::cout);
   //oa << gs;
}

void BiddingTest::oneToFive()
{
   std::list<choice> cl = {{"1", choicetype::bid}, // player1 bid 1
                           {"5", choicetype::bid}}; // player2 bid 5

   choiceSimulation(cl, gameEngine);

   // output gamestate
   //boost::archive::text_oarchive oa(std::cout);
   //oa << gs;
}
