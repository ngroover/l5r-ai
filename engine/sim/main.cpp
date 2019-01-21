#include <cstdlib>
#include <iostream>
#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"

using namespace std;

int main(int argc, char *argv[])
{
   cout << "L5R Game simulator" << endl;

   std::string name;
   cout << "Name:";
   cin >> name;

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

   game.run(true);
   return 0;
}
