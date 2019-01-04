#ifndef _REGROUP_TEST_H_
#define _REGROUP_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class RegroupTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( RegroupTest );
   CPPUNIT_TEST( discardNothing );
   CPPUNIT_TEST( discardEverything );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void discardNothing();
   void discardEverything();

private:
   l5r::engine *gameEngine;
};

#endif // _REGROUP_TEST_H_
