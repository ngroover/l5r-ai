#include "actionbuildertest.h"
#include "mctsactionbuilder.h"
#include "engine.h"
#include "policyencoder.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include <cstring>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( ActionBuilderTest );

void ActionBuilderTest::setUp()
{
   std::unique_ptr<l5r::agent> me = std::make_unique<l5r::cpuagent>("me", l5r::decklists[0]);
   std::unique_ptr<l5r::agent> cpu = std::make_unique<l5r::cpuagent>("cpu", l5r::decklists[1]);

   game = new engine(std::move(me), std::move(cpu)); 
   gamestate gs = game->getGameState();
   polEncoder = new PolicyEncoder();
   polEncoder->setupMap(&gs);
   builder = new MctsActionBuilder(game, polEncoder);
}

void ActionBuilderTest::tearDown()
{
   delete builder;
   delete polEncoder;
   delete game;
}

void ActionBuilderTest::checkBuild()
{
   CPPUNIT_ASSERT(true);
}
