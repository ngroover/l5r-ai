#ifndef _MCTS_TREE_H_
#define _MCTS_TREE_H_

#include <memory>

namespace l5r
{
   class MctsStateNode;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   class MctsTree
   {
      public:
         MctsTree();
         ~MctsTree();

         void addNewState(MctsStateNodePtr newState);
         void reset(MctsStateNodePtr root);

         void traverse();

         MctsStateNodePtr getCurrent();

      private:
         std::list<MctsStateNodePtr> globalStateList;
         MctsStateNodePtr currentState;
         

   };
};
#endif // _MCTS_TREE_H_
