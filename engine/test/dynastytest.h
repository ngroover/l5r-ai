#ifndef _DYNASTY_TEST_H_
#define _DYNASTY_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class DynastyTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( DynastyTest );
   CPPUNIT_TEST( passEverything );
   CPPUNIT_TEST( oneCharacterEach );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void passEverything();
   void oneCharacterEach();
private:
   l5r::engine *gameEngine;
};

#endif // _DYNASTY_TEST_H_
