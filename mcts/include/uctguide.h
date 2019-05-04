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
         UctGuide(double exploration);
         ~UctGuide();

         
         virtual MctsActionNodePtr chooseAction(int stateNodeVisits,
                                 std::list<MctsActionNodePtr> actions,
                                 bool negativeValue);
      private:
         double exploration;
   };
};
#endif // _UCT_GUIDE_H_
