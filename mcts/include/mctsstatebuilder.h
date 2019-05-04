#ifndef _MCTS_STATE_BUILDER_H_
#define _MCTS_STATE_BUILDER_H_

#include <memory>
#include "state/gamestate.h"

namespace l5r
{
   class GamestateEncoder;
   class PolicyEncoder;
   class GameSession;
   class GameGraph;
   class engine;
   class MctsStateNode;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   typedef std::vector<double> GamestateVector;
   typedef std::vector<double> PolicyVector;

   class MctsStateBuilder
   {
      public:
         MctsStateBuilder(GamestateEncoder *encoder, PolicyEncoder *polEncoder, GameGraph *graph, GameSession *session);
         ~MctsStateBuilder();


         MctsStateNodePtr buildState(gamestate state);
      private:
         // TODO: use less pointers. this is c++!
         GamestateEncoder *encoder;
         PolicyEncoder *polEncoder;
         GameGraph *graph;
         GameSession *session;

         PolicyVector policyVector;
         GamestateVector gameVector;

         std::list<MctsStateNodePtr> entireList;
   };
}
#endif // _MCTS_STATE_BUILDER_H_
