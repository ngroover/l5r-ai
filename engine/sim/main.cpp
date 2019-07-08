#include <cstdlib>
#include <iostream>
#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "decklistmanager.h"
#include <memory>

using namespace std;

int main(int argc, char *argv[])
{
   cout << "L5R Game simulator" << endl;
   std::unique_ptr<l5r::DecklistManager> deckManager = std::make_unique<l5r::DecklistManager>("./decks/data");

   std::string name;
   cout << "Name:";
   cin >> name;

   int i=1;
   int decknum=0;
   std::vector<std::string> deck_choices = {"Lion Suggested Deck", "Crane Suggested Deck"};

   for(auto d: deck_choices)
   {
      cout << "[" << i++ << ".] " << d <<endl;
   }
   cout << "Choose your deck: ";
   cin >> decknum;

   std::unique_ptr<l5r::agent> me = std::make_unique<l5r::humanagent>(name, *deckManager->findDeck(deck_choices[decknum-1]));

   cout << "Choose cpu deck: ";
   cin >> decknum;

   std::unique_ptr<l5r::agent> cpu = std::make_unique<l5r::humanagent>("cpu", *deckManager->findDeck(deck_choices[decknum-1]));

   l5r::engine game(std::move(me), std::move(cpu)); 

   game.run(true);
   return 0;
}
