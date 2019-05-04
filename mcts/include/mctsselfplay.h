#ifndef _MCTS_SELF_PLAY_H_
#define _MCTS_SELF_PLAY_H_

#include <memory>
#include <list>

namespace l5r
{
   class MctsTree;
   typedef std::unique_ptr<MctsTree> MctsTreePtr;
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;

   class MctsSelfPlay
   {
      public:
         MctsSelfPlay(MctsTreePtr tree, int episodes, int iterations);
         ~MctsSelfPlay();

         void playout();

      private:

         void backPropagate(std::list<MctsActionNodePtr> history);
         void episode();

         int episodes, iterations;
         MctsTreePtr tree;
   };
};
#endif // _MCTS_SELF_PLAY_H_
