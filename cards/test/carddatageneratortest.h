#ifndef _CARD_DATA_GENERATOR_TEST_H_
#define _CARD_DATA_GENERATOR_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include "carddatagenerator.h"
#include <memory>


class CardDataGeneratorTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( CardDataGeneratorTest );
   CPPUNIT_TEST( characterTest );
   CPPUNIT_TEST( holdingTest );
   CPPUNIT_TEST( strongholdTest );
   CPPUNIT_TEST( provinceTest );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void characterTest();
   void holdingTest();
   void strongholdTest();
   void provinceTest();

private:
   std::unique_ptr<l5r::CardDataGenerator> generator;
};

#endif // _CARD_DATA_GENERATOR_TEST_H_
