#ifndef _MCTS_ACTION_BUILDER_H_
#define _MCTS_ACTION_BUILDER_H_

#include <memory>

namespace l5r
{
   class MctsStateNode;
   class PolicyEncoder;
   class engine;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   typedef std::shared_ptr<engine> enginePtr;
   class MctsActionBuilder
   {
      public:
         MctsActionBuilder(enginePtr eng, PolicyEncoder *encoder);
         ~MctsActionBuilder();


         void buildActions(MctsStateNodePtr stateNode);
      private:
         enginePtr eng;
         PolicyEncoder *encoder;
   };
}
#endif // _MCTS_ACTION_BUILDER_H_
