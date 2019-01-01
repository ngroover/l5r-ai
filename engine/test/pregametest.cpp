#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "pregametest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PregameTest );

void PregameTest::setUp()
{
   std::unique_ptr<l5r::agent> lion = std::make_unique<l5r::humanagent>("testplayer1", l5r::decklists[0]);
   std::unique_ptr<l5r::agent> crane = std::make_unique<l5r::humanagent>("testplayer2", l5r::decklists[1]);

   gameEngine = new l5r::engine(std::move(lion), std::move(crane)); 
}

void PregameTest::tearDown()
{
   delete gameEngine;
}

void PregameTest::testStrongholdDecision()
{
  CPPUNIT_FAIL( "not implemented" );
}

