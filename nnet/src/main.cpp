#include <iostream>
#include "gamegraph.h"
#include "gamesession.h"

using namespace l5r;

int main(int argc, char *argv[])
{
   std::cout << "Neural Network Test" << std::endl;
   srand(time(NULL));

   // graph with batch of 5 and learning rate of 0.01
   GameGraph fiverings(2, 0.01);

   GameSession sampleSession(&fiverings);

   fiverings.init(&sampleSession);
   
   // make some random data
   const int theSize = 638*2;
   double input[theSize];
   for(int i=0;i<theSize;i++)
   {
      input[i] = ((double)(rand() % 3)) - 1.0;
   }

   double result;
   double nextresult;
   // compute network
   fiverings.compute(&sampleSession, input, 638, &result);

   std::cout << "The result is " << result << std::endl;

   double desired[] = {0.75, 0.50};

   // train network
   for(int i=0;i < 1000; i++)
   {
      fiverings.train(&sampleSession, input, theSize, desired, 2);
   }

   // recompute network
   fiverings.compute(&sampleSession, input, 638, &nextresult);

   std::cout << "The result now is " << nextresult << std::endl;

   return 0;
}
