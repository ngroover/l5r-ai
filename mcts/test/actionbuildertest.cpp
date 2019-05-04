#include "actionbuildertest.h"
#include "mctsactionbuilder.h"
#include "engine.h"
#include "policyencoder.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"
#include "mctsstatenode.h"
#include "mctsactionnode.h"
#include <cstring>

using namespace l5r;

CPPUNIT_TEST_SUITE_REGISTRATION( ActionBuilderTest );

void ActionBuilderTest::setUp()
{
   std::unique_ptr<l5r::agent> me = std::make_unique<l5r::cpuagent>("me", l5r::decklists[0]);
   std::unique_ptr<l5r::agent> cpu = std::make_unique<l5r::cpuagent>("cpu", l5r::decklists[1]);

   std::shared_ptr<engine> game = std::make_shared<engine>(std::move(me), std::move(cpu)); 
   gamestate gs = game->getGameState();
   polEncoder = new PolicyEncoder();
   polEncoder->setupMap(&gs);
   builder = new MctsActionBuilder(game, polEncoder);
}

void ActionBuilderTest::tearDown()
{
   delete builder;
   delete polEncoder;
}

void ActionBuilderTest::checkBuild()
{
   double policy[255];
   for(int i=0;i<255; i++)
   {
      policy[i] = 0.5;
   }
   PolicyVector pv(policy, policy+255);

   std::cout << "Sizeof policy=" << sizeof(policy) << std::endl;
   std::cout << "polencoder =" << polEncoder->getTotalSize() << std::endl;

   gamestate gs = game->getGameState();

   MctsStateNodePtr stateNode = std::make_shared<MctsStateNode>(gs, pv, 0.75, false);

   builder->buildActions(stateNode);

   std::list<MctsActionNodePtr> listActions = stateNode->getChildActions();
   for( auto l : listActions)
   {
      std::cout << l->getChoice().getText() << " Probability = " << l->getProbability() << std::endl;
   }

   //CPPUNIT_ASSERT_EQUAL();
}
