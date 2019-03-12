#ifndef _CHARACTER_SLOT_TEST_H_
#define _CHARACTER_SLOT_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

namespace l5r
{
   class CharacterCardSlot;
};

class CharacterSlotTest : public CppUnit::TestFixture
{
   CPPUNIT_TEST_SUITE( CharacterSlotTest );
   CPPUNIT_TEST( checkState );
   CPPUNIT_TEST( checkFate );
   CPPUNIT_TEST( checkBowed );
   CPPUNIT_TEST( checkRevealed );
   CPPUNIT_TEST_SUITE_END();

public:
   void setUp();
   void tearDown();

   void checkState();
   void checkFate();
   void checkBowed();
   void checkRevealed();


   void matchState(double *input, int position, int size);

private:
   l5r::CharacterCardSlot *charSlot;
};

#endif // _CHARACTER_SLOT_TEST_H_
