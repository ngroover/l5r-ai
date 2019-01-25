#ifndef _MCTS_SELF_PLAY_H_
#define _MCTS_SELF_PLAY_H_

namespace l5r
{
   class engine;
   class MctsTree;
   class MctsSelfPlay
   {
      public:
         MctsSelfPlay(engine *eng, int episodes, int iterations);
         ~MctsSelfPlay();

         void playout();

      private:
         void episode(MctsStateNodePtr statenode);

         engine *eng;
         int episodes, iterations;
         MctsTree tree;
   };
};
#endif // _MCTS_SELF_PLAY_H_
