#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "biddingtest.h"
#include "decision.h"
#include <algorithm>
#include <fstream>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( BiddingTest );

void BiddingTest::setUp()
{
   std::unique_ptr<agent> lion = std::make_unique<humanagent>("testplayer1", decklists[0]);
   std::unique_ptr<agent> crane = std::make_unique<humanagent>("testplayer2", decklists[1]);

   gameEngine = new engine(std::move(lion), std::move(crane)); 
}

void BiddingTest::tearDown()
{
   delete gameEngine;
}

void BiddingTest::tieAtFive()
{
   std::string serialized = "22 serialization::archive 14 0 1 0 0 104 0 32 33 34 35 36 37 38 39 40 41 42 43 44 45 30 31 28 29 26 26 27 27 70 71 72 73 74 75 76 77 78 79 56 57 58 59 60 61 62 63 64 65 66 67 68 69 1 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 30 31 31 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 0 2 3 4 5 6 2 6 0 0 0 0 0 0 17 0 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 0 0 20 0 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 4 0 22 23 24 25 0 0 1 0 0 4 0 0 0 47 0 0 0 48 4 1 0 49 2 0 0 50 3 0 0 51 46 0 0 1 0 0 0 1 0 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 12 1 1 0 17 0 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 0 0 20 0 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 4 0 74 75 76 77 0 0 55 4 0 99 52 0 0 100 53 0 0 101 54 0 0 103 56 1 0 102 98 1 0 55 0 3 0 0 0 0 0 0 0 0 11 2 0 0 0 0 0 0 0 0 0 5 0 0 0 0 0 1 0 2 0 3 0 4 0 0";

   std::stringstream ss;
   ss << serialized;
   gamestate gs;
   boost::archive::text_iarchive ia(ss);
   ia >> gs;

   gameEngine->setGameState(gs);

   decision d = gameEngine->getDecision();

   // bids 1 through 5
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   auto choiceList = d.getChoiceList().begin();
   auto savedChoice = d.getChoiceList().begin();
   while( choiceList != d.getChoiceList().end())
   {
      std::cout << choiceList->getText() << std::endl;
      if(choiceList->getType() == choicetype::bid &&
         choiceList->getNumber() == 5)
      {
         savedChoice = choiceList;
      }
      choiceList++;
   }

   // player 1 bid 5
   gameEngine->doAction(*savedChoice);

   gs = gameEngine->getGameState();

   d = gameEngine->getDecision();

   // bids 1 through 5
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   choiceList = d.getChoiceList().begin();
   savedChoice = d.getChoiceList().begin();
   while( choiceList != d.getChoiceList().end())
   {
      std::cout << choiceList->getText() << std::endl;
      if(choiceList->getType() == choicetype::bid &&
         choiceList->getNumber() == 5)
      {
         savedChoice = choiceList;
      }
      choiceList++;
   }

   // player 2 bid 5
   gameEngine->doAction(*savedChoice);

   gs = gameEngine->getGameState();

   // honor should stay as it was at 12 and 11
   CPPUNIT_ASSERT_EQUAL(gs.player1State.honorTokens, 12);
   CPPUNIT_ASSERT_EQUAL(gs.player2State.honorTokens, 11);

   // cards should go up by 5
   CPPUNIT_ASSERT_EQUAL(gs.player1State.conflictHand.size(), (unsigned int)9);
   CPPUNIT_ASSERT_EQUAL(gs.player2State.conflictHand.size(), (unsigned int)9);

   // output gamestate
   boost::archive::text_oarchive oa(std::cout);
   oa << gs;
}
