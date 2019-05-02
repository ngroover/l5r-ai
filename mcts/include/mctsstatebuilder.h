#ifndef _MCTS_STATE_BUILDER_H_
#define _MCTS_STATE_BUILDER_H_

#include <memory>
#include "state/gamestate.h"
#include "mctsstatenode.h"

namespace l5r
{
   class GamestateEncoder;
   class PolicyEncoder;
   class GameSession;
   class GameGraph;
   class engine;
   typedef std::vector<double> GamestateVector;

   class MctsStateBuilder
   {
      public:
         MctsStateBuilder(GamestateEncoder *encoder, PolicyEncoder *polEncoder, GameGraph *graph, GameSession *session);
         ~MctsStateBuilder();


         MctsStateNode buildState(gamestate state);
      private:
         // TODO: use less pointers. this is c++!
         GamestateEncoder *encoder;
         PolicyEncoder *polEncoder;
         GameGraph *graph;
         GameSession *session;

         PolicyVector policyVector;
         GamestateVector gameVector;
   };
}
#endif // _MCTS_STATE_BUILDER_H_
