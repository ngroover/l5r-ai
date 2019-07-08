#include <cstdlib>
#include <iostream>
#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "decklistmanager.h"
#include "mctsstatebuilder.h"
#include "mctsactionbuilder.h"
#include "mctsselfplay.h"
#include "mctstree.h"
#include "uctguide.h"
#include "mostvisitedguide.h"
#include "policyencoder.h"
#include "gamestateencoder.h"
#include "gamegraph.h"
#include "gamesession.h"
#include "mctsstatenode.h"
#include "gameplaytrainer.h"

using namespace std;
using namespace l5r;

int main(int argc, char *argv[])
{
   std::cout << "Self play simulator" << std::endl;
   std::unique_ptr<DecklistManager> deckManager = std::make_unique<DecklistManager>("./decks/data");

   std::unique_ptr<agent> player1 = std::make_unique<humanagent>("testplayer1", *deckManager->findDeck("Lion Suggested Deck"));
   std::unique_ptr<agent> player2 = std::make_unique<humanagent>("testplayer2", *deckManager->findDeck("Crane Suggested Deck"));

   
   std::shared_ptr<engine> game = std::make_shared<engine>(std::move(player1), std::move(player2)); 

   gamestate gs = game->getGameState();

   GamestateEncoder encoder;
   encoder.setupMap(&gs);
   PolicyEncoder polEncoder;
   polEncoder.setupMap(&gs);

   GameGraph graph(5, 0.5);

   GameSession session(&graph);
   graph.init(&session);

   std::shared_ptr<MctsStateBuilder> mctsStatebuilder = std::make_shared<MctsStateBuilder>(&encoder, &polEncoder, &graph, &session);

   MctsStateNodePtr initial = mctsStatebuilder->buildState(gs);

   std::unique_ptr<MctsActionBuilder> mctsActionbuilder = std::make_unique<MctsActionBuilder>(game, &polEncoder);

   std::unique_ptr<MctsGuide> p1Guide = std::make_unique<UctGuide>(0.5, true);
   std::unique_ptr<MctsGuide> p2Guide = std::make_unique<UctGuide>(0.5, false);
   std::unique_ptr<MctsGuide> checkpointGuide = std::make_unique<MostVisitedGuide>();

   std::unique_ptr<MctsTree> tree = std::make_unique<MctsTree>(std::move(mctsActionbuilder), mctsStatebuilder,
      std::move(game), initial);


   l5r::MctsSelfPlay mcts(std::move(p1Guide), std::move(p2Guide), std::move(checkpointGuide), std::move(tree), 10, 10);

   mcts.playout();

   GameplayTrainer trainer(mctsStatebuilder->getStateList(), &graph, &session, &encoder, &polEncoder);

   trainer.train(1);

   return 0;
}
