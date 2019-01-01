#ifndef _PREGAME_TEST_H_
#define _PREGAME_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class PregameTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( PregameTest );
   CPPUNIT_TEST( testStrongholdDecision );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void testStrongholdDecision();
private:
   l5r::engine *gameEngine;
};

#endif // _PREGAME_TEST_H_
