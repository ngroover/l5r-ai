#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "pregametest.h"
#include "decision.h"
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
   decision d = gameEngine->getDecision();
   // should get to choose from 5 provinces
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   gamestate gs = gameEngine->getGameState();
   CPPUNIT_ASSERT_EQUAL(gs.player1State.provinceArea.size(), (unsigned int)5);

   // find pilgrimage
   auto pilgrimage = std::find(gs.cardIds.begin(), gs.cardIds.end(), cards::pilgrimage);
   int pilgrimage_index=std::distance(gs.cardIds.begin(), pilgrimage);

   auto provList = gs.player1State.provinceArea.begin();
   auto choiceList = d.getChoiceList().begin();
   auto savedChoice = d.getChoiceList().begin();
   while(provList != gs.player1State.provinceArea.end() &&
      choiceList != d.getChoiceList().end())
   {
      CPPUNIT_ASSERT_EQUAL(provList->provinceCard, choiceList->getNumber());
      // find pilgrimage
      if(choiceList->getNumber() == pilgrimage_index)
      {
         savedChoice=choiceList;
      }
      provList++;
      choiceList++;
   }

   gameEngine->doAction(*savedChoice);

   // make sure one of the provinces was removed from area and set as stronghold province
   gs = gameEngine->getGameState();
   CPPUNIT_ASSERT_EQUAL(gs.player1State.provinceArea.size(), (unsigned int)4);
   CPPUNIT_ASSERT_EQUAL(gs.player1State.strongholdProvince, pilgrimage_index);

   d = gameEngine->getDecision();
   // should get to choose from 5 provinces
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   // find rally_to_the_cause
   auto rally = std::find(gs.cardIds.begin(), gs.cardIds.end(), cards::rally_to_the_cause);
   int rally_index=std::distance(gs.cardIds.begin(), rally);

   provList = gs.player2State.provinceArea.begin();
   choiceList = d.getChoiceList().begin();
   while(provList != gs.player2State.provinceArea.end() &&
      choiceList != d.getChoiceList().end())
   {
      CPPUNIT_ASSERT_EQUAL(provList->provinceCard, choiceList->getNumber());
      // find rally
      if(choiceList->getNumber() == rally_index)
      {
         savedChoice=choiceList;
      }
      provList++;
      choiceList++;
   }

   gameEngine->doAction(*savedChoice);

   // make sure one of the provinces was removed from area and set as stronghold province
   gs = gameEngine->getGameState();
   CPPUNIT_ASSERT_EQUAL(gs.player2State.provinceArea.size(), (unsigned int)4);
   CPPUNIT_ASSERT_EQUAL(gs.player2State.strongholdProvince, rally_index);

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

   decision d = gameEngine->getDecision();

   // should be 4 choices plus a pass choice
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   auto choiceList = d.getChoiceList().begin();
   auto savedChoice = d.getChoiceList().begin();
   while( choiceList != d.getChoiceList().end())
   {
      std::cout << choiceList->getText() << std::endl;
      if(choiceList->getType() == choicetype::pass)
      {
         savedChoice = choiceList;
      }
      choiceList++;
   }

   //player1 pass dynasty mulligan
   gameEngine->doAction(*savedChoice);

   gs = gameEngine->getGameState();

   d = gameEngine->getDecision();

   // should be 4 choices plus a pass choice
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   choiceList = d.getChoiceList().begin();
   savedChoice = d.getChoiceList().begin();
   while( choiceList != d.getChoiceList().end())
   {
      std::cout << choiceList->getText() << std::endl;
      if(choiceList->getType() == choicetype::pass)
      {
         savedChoice = choiceList;
      }
      choiceList++;
   }

   //player2 pass dynasty mulligan
   gameEngine->doAction(*savedChoice);

   gs = gameEngine->getGameState();

   d = gameEngine->getDecision();

   // should be 4 choices plus a pass choice
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   choiceList = d.getChoiceList().begin();
   savedChoice = d.getChoiceList().begin();
   while( choiceList != d.getChoiceList().end())
   {
      std::cout << choiceList->getText() << std::endl;
      if(choiceList->getType() == choicetype::pass)
      {
         savedChoice = choiceList;
      }
      choiceList++;
   }
   
   //player1 pass conflict mulligan
   gameEngine->doAction(*savedChoice);

   gs = gameEngine->getGameState();

   d = gameEngine->getDecision();

   // should be 4 choices plus a pass choice
   CPPUNIT_ASSERT_EQUAL(d.getChoiceList().size(), (unsigned int)5);

   choiceList = d.getChoiceList().begin();
   savedChoice = d.getChoiceList().begin();
   while( choiceList != d.getChoiceList().end())
   {
      std::cout << choiceList->getText() << std::endl;
      if(choiceList->getType() == choicetype::pass)
      {
         savedChoice = choiceList;
      }
      choiceList++;
   }

   //player2 pass conflict mulligan
   gameEngine->doAction(*savedChoice);

   gs = gameEngine->getGameState();

   // output gamestate
   //boost::archive::text_oarchive oa(std::cout);
   //oa << gs;
}

