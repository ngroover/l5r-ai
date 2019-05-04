#ifndef _MCTS_GUIDE_H_
#define _MCTS_GUIDE_H_

#include <list>
#include <memory>

namespace l5r
{
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   class MctsGuide
   {
      public:
         MctsGuide();
         ~MctsGuide();

      virtual MctsActionNodePtr chooseAction(int stateNodeVisits,
                                 std::list<MctsActionNodePtr> actions)=0;
      
   };
};

#endif // _MCTS_GUIDE_H_
