#ifndef _UCT_GUIDE_H_
#define _UCT_GUIDE_H_

#include <list>
#include <memory>
#include "mctsguide.h"

namespace l5r
{
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   class UctGuide : public MctsGuide
   {
      public:
         UctGuide(double exploration, bool maximize);
         ~UctGuide();

         
         virtual MctsActionNodePtr chooseAction(int stateNodeVisits,
                                 std::list<MctsActionNodePtr> actions);
      private:
         double exploration;
         bool maximize;
   };
};
#endif // _UCT_GUIDE_H_
