#include <iostream>
#include "gamegraph.h"
#include "gamesession.h"
#include <unistd.h>

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
      input[i] = (double)(rand() % 2);
   }

   // random policy
   double policy[24*2];
   policy[0] = 0.05;
   policy[1] = 0.10;
   policy[2] = 0.15;
   policy[3] = 0.20;
   policy[4] = 0.25;
   policy[5] = 0.30;
   policy[6] = 0.35;
   policy[7] = 0.40;
   policy[8] = 0.45;
   policy[9] = 0.50;
   policy[10] = 0.55;
   policy[11] = 0.60;
   policy[12] = 0.65;
   policy[13] = 0.70;
   policy[14] = 0.75;
   policy[15] = 0.80;
   policy[16] = 0.85;
   policy[17] = 0.90;
   policy[18] = 0.95;
   policy[19] = 0.90;
   policy[20] = 0.85;
   policy[21] = 0.80;
   policy[22] = 0.75;
   policy[23] = 0.70;
   policy[24] = 0.65;
   policy[25] = 0.60;
   policy[26] = 0.55;
   policy[27] = 0.50;
   policy[28] = 0.45;
   policy[29] = 0.40;
   policy[30] = 0.35;
   policy[31] = 0.30;
   policy[32] = 0.25;
   policy[33] = 0.20;
   policy[34] = 0.15;
   policy[35] = 0.10;
   policy[36] = 0.05;
   policy[37] = 0.10;
   policy[38] = 0.15;
   policy[39] = 0.20;
   policy[40] = 0.25;
   policy[41] = 0.30;
   policy[42] = 0.35;
   policy[43] = 0.40;
   policy[44] = 0.45;
   policy[45] = 0.50;
   policy[46] = 0.55;
   policy[47] = 0.60;

   double result;
   double nextresult;

   double resultpolicy[24];
   // compute network
   fiverings.compute(&sampleSession, input, 638, &result, resultpolicy, 24);

   std::cout << "The result is " << result << std::endl;
   std::cout << "Policy ";
   for(int i=0;i< 24;i++)
   {
      std::cout << resultpolicy[i] << " ";
   }
   std::cout << std::endl;

   // compute network
   fiverings.compute(&sampleSession, &input[638], 638, &result, resultpolicy, 24);

   std::cout << "The result is " << result << std::endl;
   std::cout << "Policy ";
   for(int i=0;i< 24;i++)
   {
      std::cout << resultpolicy[i] << " ";
   }
   std::cout << std::endl;

   double desired[] = {0.75, 0.50};

   // train network
   for(int i=0;i < 100; i++)
   {
      fiverings.train(&sampleSession, input, theSize, desired, 2, policy, 48);
      //sleep(5);
   }

   // recompute network
   fiverings.compute(&sampleSession, input, 638, &nextresult, resultpolicy, 24);

   std::cout << "The result1 now is " << nextresult << std::endl;
   std::cout << "Policy ";
   for(int i=0;i< 24;i++)
   {
      std::cout << resultpolicy[i] << " ";
   }
   std::cout << std::endl;

   // recompute network
   fiverings.compute(&sampleSession, &input[638], 638, &nextresult, resultpolicy, 24);

   std::cout << "The result2 now is " << nextresult << std::endl;
   std::cout << "Policy ";
   for(int i=0;i< 24;i++)
   {
      std::cout << resultpolicy[i] << " ";
   }
   std::cout << std::endl;

   return 0;
}
