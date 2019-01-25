#ifndef _MCTS_STATE_NODE_H_
#define _MCTS_STATE_NODE_H_

#include <list>
#include <memory>

namespace l5r
{
   class gamestate;
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   class MctsStateNode
   {
      public:
         MctsStateNode(gamestate &gs);
         ~MctsStateNode();

         bool hasChildActions();
         bool isLeaf();
         gamestate &getState();

      private:
         std::list<MctsActionNode> childActions;
         gamestate state;
         int visits;
         double value;
         bool isLeaf;

   };
};
#endif // _MCTS_STATE_NODE_H_
