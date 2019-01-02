#ifndef _GAMESTATE_TEST_H_
#define _GAMESTATE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class GamestateTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( GamestateTest );
   CPPUNIT_TEST( testSerialize );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void testSerialize();
private:
   l5r::engine *gameEngine;
};

#endif // _GAMESTATE_TEST_H_
