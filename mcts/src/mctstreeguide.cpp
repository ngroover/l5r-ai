#include "mctstreeguide.h"
#include <cmath>

using namespace l5r;

MctsTreeGuide::MctsTreeGuide(double exploration, bool inverse) : exploration(exploration), inverse(inverse)
{
}

MctsTreeGuide::~MctsTreeGuide()
{
}


MctsActionNodePtr calculateBestAction(int stateVisited, MctsActionNodeList actionList)
{
   double max_upper_confidence=-100;
   MctsActionNodePtr bestAction;
   for(auto a: actionList)
   {
      double q = a->getReward();
      if(inverse)
      {
         q = (1.0 - q);
      }

      upper_confidence = q + (a->getProbability() + 
            (exploration * sqrt((log(stateVisited+1))/(a->getVisits()+1))))/2.0;

      if(upper_confidence > max_upper_confidence)
      {
         max_upper_confidence = upper_confidence;
         bestAction = a;
      }
   }
   return bestAction;
}
