#ifndef _BIDDING_TEST_H_
#define _BIDDING_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class engine;
};

class BiddingTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( BiddingTest );
   CPPUNIT_TEST( tieAtFive );
//   CPPUNIT_TEST( tieAtOne );
 //  CPPUNIT_TEST( oneToFive );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void tieAtFive();
   void tieAtOne();
   void oneToFive();
private:
   l5r::engine *gameEngine;
};

#endif // _BIDDING_TEST_H_
