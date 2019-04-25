#ifndef _MCTS_STATE_BUILDER_H_
#define _MCTS_STATE_BUILDER_H_

#include <memory>
#include "state/gamestate.h"
#include "mctsstatenode.h"

namespace l5r
{
   class GamestateBuilder;
   class GameGraph;
   class engine;

   class MctsStateBuilder
   {
      public:
         MctsStateBuilder(GamestateBuilder *builder, GameGraph *graph);
         ~MctsStateBuilder();


         MctsStateNode buildState(gamestate &state);
      private:
         GamestateBuilder *builder;
         GameGraph *graph;
   };
}
#endif // _MCTS_STATE_BUILDER_H_
