#include <cstdlib>
#include <iostream>
#include <glog/logging.h>

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>

using namespace std;

int main(int argc, char *argv[])
{
   google::InitGoogleLogging(argv[0]);

   // Get the top level suite from the registry
   CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

   // Adds the test to the list of test to run
   CppUnit::TextUi::TestRunner runner;
   runner.addTest( suite );

   // Change the default outputter to a compiler error format outputter
   runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                     std::cerr ) );
   // Run the tests.
   bool wasSucessful = runner.run();

   // Return error code 1 if the one of test failed.
   return wasSucessful ? 0 : 1;
}
