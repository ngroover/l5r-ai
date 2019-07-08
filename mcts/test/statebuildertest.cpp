#include "statebuildertest.h"
#include "mctsstatebuilder.h"
#include "gamestateencoder.h"
#include "engine.h"
#include "policyencoder.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "decklistmanager.h"
#include "mctsstatenode.h"
#include "mctsactionnode.h"
#include "gamegraph.h"
#include "gamesession.h"
#include <cstring>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( StateBuilderTest );

void StateBuilderTest::setUp()
{
   std::unique_ptr<DecklistManager> deckManager = std::make_unique<DecklistManager>("./decks/data");

   std::unique_ptr<agent> me = std::make_unique<humanagent>("me", *deckManager->findDeck("Lion Suggested Deck"));
   std::unique_ptr<agent> cpu = std::make_unique<humanagent>("cpu", *deckManager->findDeck("Crane Suggested Deck"));

   game = new engine(std::move(me), std::move(cpu)); 
   gamestate gs = game->getGameState();
   polEncoder = new PolicyEncoder();
   polEncoder->setupMap(&gs);
   encoder = new GamestateEncoder();
   encoder->setupMap(&gs);
   graph = new GameGraph(5, 0.01);
   session = new GameSession(graph);
   graph->init(session);
   builder = new MctsStateBuilder(encoder, polEncoder, graph, session);
}

void StateBuilderTest::tearDown()
{
   delete builder;
   delete polEncoder;
   delete encoder;
   delete game;
   delete session;
   delete graph;
}

void StateBuilderTest::checkBuild()
{
   double policy[255];
   for(int i=0;i<255; i++)
   {
      policy[i] = 0.5;
   }

   std::cout << "Sizeof policy=" << sizeof(policy) << std::endl;
   std::cout << "polencoder =" << polEncoder->getTotalSize() << std::endl;

   gamestate gs = game->getGameState();

   MctsStateNodePtr node = builder->buildState(gs);

   CPPUNIT_ASSERT_EQUAL(node->isLeaf(), false);
   CPPUNIT_ASSERT_EQUAL(node->hasChildActions(),false);
}
