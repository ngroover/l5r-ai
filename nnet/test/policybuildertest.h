#ifndef _POLICY_BUILDER_TEST_H_
#define _POLICY_BUILDER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class PolicyBuilder;
};

class PolicyBuilderTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( PolicyBuilderTest );
   CPPUNIT_TEST( checkSize );
   CPPUNIT_TEST( checkSetPolicy );
   CPPUNIT_TEST( checkGetPolicy );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void checkSetPolicy();
   void checkGetPolicy();
   void checkSize();

private:
   l5r::PolicyBuilder *builder;
};

#endif // _POLICY_BUILDER_TEST_H_
