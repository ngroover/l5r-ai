#include "mostvisitedguide.h"
#include "mctsactionnode.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace l5r;

MostVisitedGuide::MostVisitedGuide(): gen(rd())
{
}

MostVisitedGuide::~MostVisitedGuide()
{
}


MctsActionNodePtr MostVisitedGuide::chooseAction(int stateNodeVisits,
                                 std::list<MctsActionNodePtr> actions)
{
   std::vector<int> probs;
   for(auto a : actions)
   {
      probs.push_back(a->getVisits());
   }
   std::discrete_distribution<int> d(probs.begin(), probs.end());

   int choice = d(gen);
   std::cout << "Randomly chose " << choice << std::endl;
   int i=0;
   for(auto a : actions)
   {
      if(choice == i)
      {
         return a;
      }
   }
}
