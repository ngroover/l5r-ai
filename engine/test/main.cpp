#include <cstdlib>
#include <iostream>
#include "pregametest.h"

using namespace std;

int main(int argc, char *argv[])
{
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

/*
   int i=1;
   int decknum=0;
   for(auto d: l5r::decklists)
   {
      cout << "[" << i++ << ".] " << d.getName() <<endl;
   }
   cout << "Choose your deck: ";
   cin >> decknum;

   std::unique_ptr<l5r::agent> me = std::make_unique<l5r::humanagent>(name, l5r::decklists[decknum-1]);

   cout << "Choose cpu deck: ";
   cin >> decknum;

   std::unique_ptr<l5r::agent> cpu = std::make_unique<l5r::cpuagent>("cpu", l5r::decklists[decknum-1]);

   l5r::engine game(std::move(me), std::move(cpu)); 
   game.run();
*/
//   return 0;
}
