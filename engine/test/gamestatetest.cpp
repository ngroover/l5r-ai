#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "gamestatetest.h"
#include "gamestate.h"
#include "decision.h"
#include <algorithm>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( GamestateTest );

void GamestateTest::setUp()
{
   std::unique_ptr<agent> lion = std::make_unique<humanagent>("testplayer1", decklists[0]);
   std::unique_ptr<agent> crane = std::make_unique<humanagent>("testplayer2", decklists[1]);

   gameEngine = new engine(std::move(lion), std::move(crane)); 
}

void GamestateTest::tearDown()
{
   delete gameEngine;
}

void GamestateTest::testSerialize()
{
   gamestate gs = gameEngine->getGameState();
   std::stringstream ss;
   boost::archive::text_oarchive oa(ss);
   oa << gs;

   gamestate gs2;
   boost::archive::text_iarchive ia(ss);
   ia >> gs2;
}
