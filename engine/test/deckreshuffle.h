#ifndef _DECK_RESHUFFLE_H_
#define _DECK_RESHUFFLE_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class DeckReshuffle : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( DeckReshuffle );
   CPPUNIT_TEST( testDynastyReshuffle );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void testDynastyReshuffle();

private:
   l5r::engine *gameEngine;
};

#endif // _PREGAME_TEST_H_
