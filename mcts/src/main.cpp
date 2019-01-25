#include <cstdlib>
#include <iostream>
#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "mctsselfplay.h"

using namespace std;

int main(int argc, char *argv[])
{
   std::cout << "Self play simulator" << std::endl;
   std::unique_ptr<l5r::agent> player1 = std::make_unique<l5r::cpuagent>("lion", l5r::decklists[0]);

   std::unique_ptr<l5r::agent> player2 = std::make_unique<l5r::cpuagent>("crane", l5r::decklists[1]);

   l5r::engine game(std::move(player1), std::move(player2)); 

   l5r::MctsSelfPlay mcts(&game, 1);

   mcts.playout();

   return 0;
}
