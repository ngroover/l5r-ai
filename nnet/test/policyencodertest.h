#ifndef _POLICY_ENCODER_TEST_H_
#define _POLICY_ENCODER_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class PolicyEncoder;
};

class PolicyEncoderTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( PolicyEncoderTest );
   CPPUNIT_TEST( encodePolicy );
   CPPUNIT_TEST( decodePolicy );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void encodePolicy();
   void decodePolicy();

private:
   l5r::PolicyEncoder *encoder;
};

#endif // _POLICY_ENCODER_TEST_H_
