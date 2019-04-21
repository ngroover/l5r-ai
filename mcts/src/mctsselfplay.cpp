#include "mctsselfplay.h"
#include "mctstree.h"
#include "mctsstatenode.h"
#include <iostream>
#include "engine.h"
#include "decision.h"

using namespace l5r;

MctsSelfPlay::MctsSelfPlay(engine *eng, int episodes, int iterations):eng(eng), episodes(episodes), iterations(iterations)
{
}


MctsSelfPlay::~MctsSelfPlay()
{
}

void MctsSelfPlay::playout()
{
   gamestate gs = eng->getGameState();
   auto root = std::make_shared<MctsStateNode>(gs);
   tree.addNewState(root);

   for(int e=0;e < episodes; e++)
   {
      std::cout << "Episode: " << e << std::endl;
      episode(root);
   }
}

void MctsSelfPlay::episode(MctsStateNodePtr statenode)
{
   bool done = false;
   tree.reset(statenode);

   while( !tree.getCurrent()->isLeaf() )
   {
      for(int i=0;i < iterations; i++)
      {
         done = false;
         while(!done)
         {
               // traverse tree
               //action = traverse

               //decision d = eng->getDecision();
               //d.getChoiceList();
               
               // determine which player
               //tree.getCurrent().getState().currentAction

               // encode gamestate using nn

               // get probabilities from nn

               //tree.getCurrent()->setValue(12345);  // from network
            if( !tree.getCurrent()->hasChildActions() )
            {
               
            }
         }
      }
   }
}
