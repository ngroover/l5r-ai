#include "policybuildertest.h"
#include "policybuilder.h"
#include <cstring>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( PolicyBuilderTest );

void PolicyBuilderTest::setUp()
{
   builder = new PolicyBuilder(30);
}

void PolicyBuilderTest::tearDown()
{
   delete builder;
}

void PolicyBuilderTest::checkSize()
{
   CPPUNIT_ASSERT_EQUAL(31, builder->getTotalSize());

   // 1 bit
   PolicyBuilder p1(2);
   CPPUNIT_ASSERT_EQUAL(1, p1.getTotalSize());

   // 2 bit
   PolicyBuilder p2(3);
   CPPUNIT_ASSERT_EQUAL(3, p2.getTotalSize());
   PolicyBuilder p3(4);
   CPPUNIT_ASSERT_EQUAL(3, p3.getTotalSize());

   // 3 bit
   PolicyBuilder p4(5);
   CPPUNIT_ASSERT_EQUAL(7, p4.getTotalSize());
   PolicyBuilder p5(6);
   CPPUNIT_ASSERT_EQUAL(7, p5.getTotalSize());
   PolicyBuilder p6(7);
   CPPUNIT_ASSERT_EQUAL(7, p6.getTotalSize());

   // 4 bit
   PolicyBuilder p7(15);
   CPPUNIT_ASSERT_EQUAL(15, p7.getTotalSize());
   //...
}

void PolicyBuilderTest::checkSetPolicy()
{
   double *rawData = builder->getRawData();
   memset(rawData, 0, sizeof(double)*builder->getTotalSize());

   std::map<int, double> policyMap = {{5, 0.20}, {10, 0.20}, {15, 0.20}, {25, 0.20}, {30, 0.20}};

   // 00101 = 5   01010 = 10   01111 = 15   11001 = 25   11110 = 30

   builder->setPolicy(policyMap);

   CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0/5.0, rawData[0], 0.01); // 1xxxx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0/3.0, rawData[1], 0.01); // 01xxx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[2], 0.01); // 11xxx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[3], 0.01); // 001xx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, rawData[4], 0.01); // 011xx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[5], 0.01); // 101xx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, rawData[6], 0.01); // 111xx
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[7], 0.01); // 0001x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[8], 0.01); // 0011x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[9], 0.01); // 0101x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[10], 0.01); // 0111x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[11], 0.01); // 1001x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[12], 0.01); // 1011x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[13], 0.01); // 1101x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[14], 0.01); // 1111x
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[15], 0.01); // 00001
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[16], 0.01); // 00011
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[17], 0.01); // 00101
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[18], 0.01); // 00111
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[19], 0.01); // 01001
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[20], 0.01); // 01011
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[21], 0.01); // 01101
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[22], 0.01); // 01111
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[23], 0.01); // 10001
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[24], 0.01); // 10011
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[25], 0.01); // 10101
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[26], 0.01); // 10111
   CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, rawData[27], 0.01); // 11001
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[28], 0.01); // 11011
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[29], 0.01); // 11101
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[29], 0.01); // 11101
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, rawData[30], 0.01); // 11111
}

void PolicyBuilderTest::checkGetPolicy()
{
   double *rawData = builder->getRawData();
   memset(rawData, 0, sizeof(double)*builder->getTotalSize());

   rawData[0] = 2.0/5.0;
   rawData[1] = 2.0/3.0;
   rawData[2] = 1.0;
   rawData[3] = 1.0;
   rawData[4] = 0.5;
   rawData[5] = 0.0;
   rawData[6] = 0.5;
   rawData[7] = 0.0;
   rawData[8] = 0.0;
   rawData[9] = 1.0;
   rawData[10] = 1.0;
   rawData[11] = 0.0;
   rawData[12] = 0.0;
   rawData[13] = 0.0;
   rawData[14] = 1.0;
   rawData[15] = 0.0;
   rawData[16] = 0.0;
   rawData[17] = 1.0;
   rawData[18] = 0.0;
   rawData[19] = 0.0;
   rawData[20] = 0.0;
   rawData[21] = 0.0;
   rawData[22] = 1.0;
   rawData[23] = 0.0;
   rawData[24] = 0.0;
   rawData[25] = 0.0;
   rawData[26] = 0.0;
   rawData[27] = 1.0;
   rawData[28] = 0.0;
   rawData[29] = 0.0;
   rawData[29] = 0.0;
   rawData[30] = 0.0;

   // 00101 = 5   01010 = 10   01111 = 15   11001 = 25   11110 = 30
   // reverse of test above
   std::list<int> validChoices = {5, 10, 15, 25, 30};

   std::map<int, double> policyMap = builder->getPolicy(validChoices);

   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, policyMap[5], 0.01);
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, policyMap[10], 0.01);
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, policyMap[15], 0.01);
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, policyMap[25], 0.01);
   CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, policyMap[30], 0.01);
}

