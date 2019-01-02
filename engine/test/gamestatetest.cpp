#include "engine.h"

#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "gamestatetest.h"
#include "gamestate.h"
#include "decision.h"
#include <algorithm>

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
   std::string str;
   std::stringstream ss;
   ss << gs;
   ss >> str;
   std::stringstream ss2;
   ss2 << str;
   ss2 >> gs;
}
