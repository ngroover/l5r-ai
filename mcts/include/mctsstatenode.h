#ifndef _MCTS_STATE_NODE_H_
#define _MCTS_STATE_NODE_H_

#include <list>
#include <memory>
#include "state/gamestate.h"

namespace l5r
{
   class gamestate;
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   class MctsStateNode
   {
      public:
         MctsStateNode(gamestate &gs, double *policy, int policySize, double value);
         ~MctsStateNode();

         bool hasChildActions();
         bool isLeaf();
         gamestate &getState();

         double *getPolicy();
         int getPolicySize();

         void addChildAction(MctsActionNodePtr child);

         std::list<MctsActionNodePtr> getChildActions();

      private:
         std::list<MctsActionNodePtr> childActions;
         gamestate state;
         int visits;
         double value;
         bool leaf;
         double *policy;
         int policySize;
   };
};
#endif // _MCTS_STATE_NODE_H_
