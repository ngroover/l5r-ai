#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "pregametest.h"
#include "decision.h"
#include <algorithm>

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
}
