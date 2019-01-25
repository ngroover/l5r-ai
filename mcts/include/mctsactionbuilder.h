#ifndef _MCTS_ACTION_BUILDER_H_
#define _MCTS_ACTION_BUILDER_H_

#include <memory>

namespace l5r
{
   class MctsStateNode;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   class MctsActionBuilder
   {
      public:
         MctsActionBuilder();
         ~MctsActionBuilder();


         void buildActions(MctsStateNodePtr stateNode);
   };
}
#endif // _MCTS_ACTION_BUILDER_H_
