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
   class MctsGuide;
   typedef std::unique_ptr<MctsGuide> MctsGuideUniquePtr;
   typedef std::shared_ptr<MctsGuide> MctsGuidePtr;

   class MctsSelfPlay
   {
      public:
         MctsSelfPlay(MctsGuideUniquePtr player1Guide, MctsGuideUniquePtr player2Guide, MctsGuideUniquePtr checkpointGuide, MctsTreePtr uniquetree, int episodes, int iterations);
         ~MctsSelfPlay();

         void playout();

      private:

         void backPropagate(std::list<MctsActionNodePtr> history);
         void episode();

         int episodes, iterations;
         MctsTreePtr tree;
         MctsGuidePtr player1Guide;
         MctsGuidePtr player2Guide;
         MctsGuidePtr checkpointGuide;
   };
};
#endif // _MCTS_SELF_PLAY_H_
