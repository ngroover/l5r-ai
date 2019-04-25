#ifndef _MCTS_ACTION_BUILDER_H_
#define _MCTS_ACTION_BUILDER_H_

#include <memory>

namespace l5r
{
   class MctsStateNode;
   class PolicyEncoder;
   class engine;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   class MctsActionBuilder
   {
      public:
         MctsActionBuilder(engine *eng, PolicyEncoder *encoder);
         ~MctsActionBuilder();


         void buildActions(MctsStateNodePtr stateNode);
      private:
         engine *eng;
         PolicyEncoder *encoder;
   };
}
#endif // _MCTS_ACTION_BUILDER_H_
