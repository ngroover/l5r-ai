#ifndef _MCTS_TREE_GUIDE_H_
#define _MCTS_TREE_GUIDE_H_

#include <memory>
#include <list>

namespace l5r
{
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   typedef std::list<MctsActionNodePtr> MctsActionNodeList;
   class MctsTreeGuide
   {
      public:
         //maximize says that we want to maximize the action value
         // otherwise we are trying to minimize the action value
         // There should be an opposing guide for each player
         // playing the game
         MctsTreeGuide(double exploration, bool inverse);
         ~MctsTreeGuide();

         MctsActionNodePtr calculateBestAction(int stateVisited, MctsActionNodeList actionList);
      private:
         double exploration;
         bool maximize;
   };
};
#endif
