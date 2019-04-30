#ifndef _MCTS_ACTION_NODE_H_
#define _MCTS_ACTION_NODE_H_

#include "choice.h"
#include <memory>

namespace l5r
{
   class MctsStateNode;
   typedef std::weak_ptr<MctsStateNode> MctsStateNodeWeakPtr;
   class MctsActionNode
   {
      public:
         MctsActionNode(choice c, double probability, MctsStateNodeWeakPtr parent);
         ~MctsActionNode();

         double getReward();

         double getProbability();

         int getVisits();

         choice getChoice();

      private:
         int visits;
         double reward;
         double probability;
         choice c;

         MctsStateNodeWeakPtr parent;
         std::list<MctsStateNodeWeakPtr> child_states;
   };
};
#endif // _MCTS_ACTION_NODE_H_
