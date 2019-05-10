#include "uctguide.h"
#include "mctsactionnode.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace l5r;

UctGuide::UctGuide(double exploration, bool maximize) : exploration(exploration),
maximize(maximize)
{
}

UctGuide::~UctGuide()
{
}


MctsActionNodePtr UctGuide::chooseAction(int stateNodeVisits,
                                 std::list<MctsActionNodePtr> actions)
{
   double maxUpperConfidence=std::numeric_limits<double>::lowest();
   MctsActionNodePtr maxAction;
   if(actions.size() == 0)
   {
      std::cout << "got no actions as input" << std::endl;
   }
   for(auto a : actions)
   {
      std::cout << "-----------" << std::endl;
      std::cout << a->getChoice().getText() << std::endl;
      double val = (maximize ? a->getReward() : -a->getReward());

      std::cout << "value=" << val << std::endl;
      double prob = a->getProbability();
      std::cout << "prob=" << prob << std::endl;

      int actionVisits = a->getVisits();
      std::cout << "visits=" << actionVisits << std::endl;


      double upper_confidence = val + (prob + (exploration * sqrt((log(stateNodeVisits+1))/(actionVisits+1))))/2.0;
      std::cout << "upper confidence=" << upper_confidence << std::endl;
      if(maxUpperConfidence < upper_confidence)
      {
         maxUpperConfidence = upper_confidence;
         maxAction = a;
         std::cout << "found a max action" << std::endl;
      }
   }

   return maxAction;
}
