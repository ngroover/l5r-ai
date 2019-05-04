#include "mctsselfplay.h"
#include "mctstree.h"
#include "mctsstatenode.h"
#include "uctguide.h"
#include <iostream>
#include "engine.h"
#include "decision.h"
#include "mctsactionnode.h"

using namespace l5r;

MctsSelfPlay::MctsSelfPlay(MctsGuideUniquePtr player1Guide, MctsGuideUniquePtr player2Guide, MctsTreePtr tree, int episodes, int iterations):
player1Guide(std::move(player1Guide)),
player2Guide(std::move(player2Guide)),
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

   while( !tree->hasReachedLeaf() )
   {
      for(int i=0;i < iterations; i++)
      {
         tree->setCheckpoint();

         done = false;

         while(!done)
         {
            bool negativeValue = !tree->getCurrent()->player1Turn();
            bool newNode;

            // traverse tree using lookahead traversal
            if(tree->getCurrent()->player1Turn())
            {
               newNode = tree->traverse(player1Guide);
            }
            else
            {
               newNode = tree->traverse(player2Guide);
            }

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
