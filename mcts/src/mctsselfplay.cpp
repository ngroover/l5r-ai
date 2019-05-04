#include "mctsselfplay.h"
#include "mctstree.h"
#include "mctsstatenode.h"
#include "uctguide.h"
#include <iostream>
#include "engine.h"
#include "decision.h"
#include "mctsactionnode.h"

using namespace l5r;

MctsSelfPlay::MctsSelfPlay(MctsTreePtr tree, int episodes, int iterations):
episodes(episodes), iterations(iterations), 
tree(std::move(tree))
{
}


MctsSelfPlay::~MctsSelfPlay()
{
}

void MctsSelfPlay::playout()
{
   for(int e=0;e < episodes; e++)
   {
      std::cout << "Episode: " << e << std::endl;
      episode();
   }
}

void MctsSelfPlay::episode()
{
   bool done = false;
   tree.reset();

   //TODO: call this file exploration self play

   // add tree checkpoints for root node
   while( !tree->hasReachedLeaf() )
   {
      for(int i=0;i < iterations; i++)
      {
         tree->setCheckpoint();

         done = false;

         while(!done)
         {
            // traverse tree using lookahead traversal
            bool newNode = tree->traverse();

            if(tree->hasReachedLeaf() || newNode)
            {
               std::list<MctsActionNodePtr> actionHistory = tree->getHistory();
               backPropagate(actionHistory);
               tree->restoreCheckpoint();
               done = true;
            }
         }
      }

         //traverse randomly weighted by traversal distribution
         //TODO: split off the guides to pass into traverse
         //tree->traverse
   }
}

void MctsSelfPlay::backPropagate(std::list<MctsActionNodePtr> history)
{
   double value = tree->getCurrent()->getValue();
   for(auto h : history)
   {
      h->adjustReward(value);
   }
}
