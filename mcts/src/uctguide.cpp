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
   for(auto a : actions)
   {
      double val = (maximize ? a->getReward() : -a->getReward());

      double prob = a->getProbability();

      int actionVisits = a->getVisits();

      double upper_confidence = val + (prob + (exploration * sqrt((log(stateNodeVisits+1))/(actionVisits+1))))/2.0;

      if(maxUpperConfidence < upper_confidence)
      {
         maxUpperConfidence = upper_confidence;
         maxAction = a;
      }
   }

   return maxAction;
}
