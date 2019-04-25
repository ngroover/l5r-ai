#ifndef _ACTION_BUILDER_TEST_H_
#define _ACTION_BUILDER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class MctsActionBuilder;
   class engine;
   class PolicyEncoder;
};

class ActionBuilderTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( ActionBuilderTest );
   CPPUNIT_TEST( checkBuild );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void checkBuild();

private:
   l5r::PolicyEncoder *polEncoder;
   l5r::MctsActionBuilder *builder;
   l5r::engine *game;
};

#endif // _ACTION_BUILDER_TEST_H_
