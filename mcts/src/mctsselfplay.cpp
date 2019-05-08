#include "mctsselfplay.h"
#include "mctstree.h"
#include "mctsstatenode.h"
#include "uctguide.h"
#include <iostream>
#include "engine.h"
#include "decision.h"
#include "mctsactionnode.h"

using namespace l5r;

MctsSelfPlay::MctsSelfPlay(MctsGuideUniquePtr player1Guide, MctsGuideUniquePtr player2Guide, MctsGuideUniquePtr checkpointGuide, MctsTreePtr uniquetree, int episodes, int iterations):
player1Guide(std::move(player1Guide)),
player2Guide(std::move(player2Guide)),
checkpointGuide(std::move(checkpointGuide)),
episodes(episodes), iterations(iterations), 
tree(std::move(uniquetree))
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
   tree->reset();

   //TODO: call this file exploration self play

   while( !tree->hasReachedLeaf() )
   {
      for(int i=0;i < iterations; i++)
      {
         std::cout << "set checkpoint" << std::flush << std::endl;
         tree->setCheckpoint();

         done = false;

         while(!done)
         {
            bool negativeValue = !tree->getCurrent()->player1Turn();
            bool newNode;

            std::cout << "traversing " << std::flush << std::endl;
            // traverse tree using lookahead traversal
            if(tree->getCurrent()->player1Turn())
            {
               newNode = tree->traverse(player1Guide);
            }
            else
            {
               newNode = tree->traverse(player2Guide);
            }
            
            std::cout << "input key...";
            std::cin.get();

            if(tree->hasReachedLeaf() || newNode)
            {
               std::cout << "reached leaf " << std::flush << std::endl;
               std::list<MctsActionNodePtr> actionHistory = tree->getHistory();
               backPropagate(actionHistory);
               tree->restoreCheckpoint();
               done = true;
            }
         }
      }

      // actually move the checkpoint
      tree->traverse(checkpointGuide);
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
