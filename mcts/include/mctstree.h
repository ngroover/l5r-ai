#ifndef _MCTS_TREE_H_
#define _MCTS_TREE_H_

#include <memory>
#include <list>
#include "mctsactionbuilder.h"
#include "mctsstatebuilder.h"

namespace l5r
{
   class MctsStateNode;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   class MctsGuide;
   typedef std::unique_ptr<MctsGuide> MctsGuidePtr;
   class engine;
   typedef std::shared_ptr<engine> enginePtr;
   class MctsActionBuilder;
   typedef std::unique_ptr<MctsActionBuilder> MctsActionBuilderPtr;
   class MctsStateBuilder;
   typedef std::unique_ptr<MctsStateBuilder> MctsStateBuilderPtr;
   class MctsTree
   {
      public:
         MctsTree(MctsGuidePtr player1Guide, MctsGuidePtr player2Guide, MctsActionBuilderPtr actionBuilder, MctsStateBuilderPtr stateBuilder, enginePtr game, MctsStateNodePtr initial);
         ~MctsTree();

         bool traverse();
         
         bool hasReachedLeaf();

         MctsStateNodePtr getCurrent();

         void setCurrent(MctsStateNodePtr newState);

         void reset();

         void setCheckpoint();
         void restoreCheckpoint();

         // TODO: simplify API to clear history and get
         std::list<MctsActionNodePtr> getHistory();

      private:
         //TODO: move this to the state builder
         // to ensure nodes are unique
         MctsStateNodePtr findNode(gamestate state);

         std::list<MctsStateNodePtr> globalStateList;
         MctsStateNodePtr currentState;
         
         MctsGuidePtr player1Guide;
         MctsGuidePtr player2Guide;
         MctsActionBuilderPtr actionBuilder;
         MctsStateBuilderPtr stateBuilder;
         enginePtr game;

         //eventually have a gamestatebuilder that can generate random initial states
         MctsStateNodePtr initialState;
         MctsStateNodePtr checkpt;

         std::list<MctsActionNodePtr> history;
   };
};
#endif // _MCTS_TREE_H_
