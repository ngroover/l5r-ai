#ifndef _CONFLICT_TEST_H_
#define _CONFLICT_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class ConflictTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( ConflictTest );
   CPPUNIT_TEST( singleConflict );
   CPPUNIT_TEST( provinceBreak );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void singleConflict();
   void provinceBreak();

private:
   l5r::engine *gameEngine;
};

#endif // _CONFLICT_TEST_H_
