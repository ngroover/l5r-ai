#ifndef _GAMESTATE_BUILDER_TEST_H_
#define _GAMESTATE_BUILDER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class GamestateBuilder;
};

class GamestateBuilderTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( GamestateBuilderTest );
   CPPUNIT_TEST( checkCharacters );
   CPPUNIT_TEST( checkHoldings );
   //CPPUNIT_TEST( checkProvinces );
   //CPPUNIT_TEST( checkRings );
   //CPPUNIT_TEST( checkPlayers );
   //CPPUNIT_TEST( checkGlobal );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void checkCharacters();
   void checkHoldings();
   void checkProvinces();
   void checkRings();
   void checkPlayers();
   void checkGlobal();

private:
   l5r::GamestateBuilder *builder;
};

#endif // _GAMESTATE_BUILDER_TEST_H_
