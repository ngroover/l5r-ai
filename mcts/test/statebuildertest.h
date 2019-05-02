#ifndef _STATE_BUILDER_TEST_H_
#define _STATE_BUILDER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class MctsStateBuilder;
   class engine;
   class PolicyEncoder;
   class GameGraph;
   class GameSession;
   class GamestateEncoder;
};

class StateBuilderTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( StateBuilderTest );
   CPPUNIT_TEST( checkBuild );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void checkBuild();

private:
   l5r::PolicyEncoder *polEncoder;
   l5r::GamestateEncoder *encoder;
   l5r::MctsStateBuilder *builder;
   l5r::GameGraph *graph;
   l5r::GameSession *session;
   l5r::engine *game;
};

#endif // _STATE_BUILDER_TEST_H_
