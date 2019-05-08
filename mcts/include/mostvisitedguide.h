#ifndef _MOST_VISITED_GUIDE_H_
#define _MOST_VISITED_GUIDE_H_

#include <list>
#include <memory>
#include "mctsguide.h"
#include <random>

namespace l5r
{
   class MctsActionNode;
   typedef std::shared_ptr<MctsActionNode> MctsActionNodePtr;
   class MostVisitedGuide : public MctsGuide
   {
      public:
         MostVisitedGuide();
         ~MostVisitedGuide();

         
         virtual MctsActionNodePtr chooseAction(int stateNodeVisits,
                                 std::list<MctsActionNodePtr> actions);
      private:
         std::random_device rd;
         std::mt19937 gen;
   };
};
#endif // _MOST_VISITED_GUIDE_H_
