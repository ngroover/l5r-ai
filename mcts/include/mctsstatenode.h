#ifndef _MCTS_STATE_NODE_H_
#define _MCTS_STATE_NODE_H_

#include <list>
#include <memory>
#include <vector>
#include "state/gamestate.h"

namespace l5r
{
   class gamestate;
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   typedef std::vector<double> PolicyVector;
   class MctsStateNode
   {
      public:
         // constructor
         MctsStateNode(gamestate gs, PolicyVector policy, double stateValue, bool leafNode);
         // destructor
         ~MctsStateNode();

         bool hasChildActions();
         bool isLeaf();
         gamestate getState();

         PolicyVector getPolicy();

         void addChildAction(MctsActionNodePtr child);

         std::list<MctsActionNodePtr> getChildActions();

      private:
         std::list<MctsActionNodePtr> childActions;
         gamestate state;
         int visits;
         double value;
         bool leaf;
         PolicyVector policy;
   };
};
#endif // _MCTS_STATE_NODE_H_
