#include <cstdlib>
#include <iostream>
#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "mctsstatebuilder.h"
#include "mctsactionbuilder.h"
#include "mctsselfplay.h"
#include "mctstree.h"
#include "uctguide.h"
#include "policyencoder.h"
#include "gamestateencoder.h"
#include "gamegraph.h"
#include "gamesession.h"

using namespace std;
using namespace l5r;

int main(int argc, char *argv[])
{
   std::cout << "Self play simulator" << std::endl;
   std::unique_ptr<l5r::agent> player1 = std::make_unique<l5r::cpuagent>("lion", l5r::decklists[0]);

   std::unique_ptr<l5r::agent> player2 = std::make_unique<l5r::cpuagent>("crane", l5r::decklists[1]);

   
   std::shared_ptr<engine> game = std::make_shared<engine>(std::move(player1), std::move(player2)); 

   gamestate gs = game->getGameState();

   GamestateEncoder encoder;
   encoder.setupMap(&gs);
   PolicyEncoder polEncoder;
   polEncoder.setupMap(&gs);

   GameGraph graph(5, 0.5);

   GameSession session(&graph);

   std::unique_ptr<MctsStateBuilder> mctsStatebuilder = std::make_unique<MctsStateBuilder>(&encoder, &polEncoder, &graph, &session);

   MctsStateNodePtr initial = mctsStatebuilder->buildState(gs);

   std::unique_ptr<MctsActionBuilder> mctsActionbuilder = std::make_unique<MctsActionBuilder>(game, &polEncoder);

   std::unique_ptr<MctsGuide> p1Guide = std::make_unique<UctGuide>(0.1);
   std::unique_ptr<MctsGuide> p2Guide = std::make_unique<UctGuide>(0.1);

   std::unique_ptr<MctsTree> tree = std::make_unique<MctsTree>(
      std::move(p1Guide), std::move(p2Guide), std::move(mctsActionbuilder), std::move(mctsStatebuilder),
      std::move(game), initial);


   l5r::MctsSelfPlay mcts(std::move(tree), 1, 1);

   mcts.playout();

   return 0;
}
