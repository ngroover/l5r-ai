#include <iostream>
#include "gamegraph.h"
#include "gamesession.h"
#include "gamestateencoder.h"
#include "policyencoder.h"
#include "engine.h"
#include <unistd.h>
#include "engine.h"
#include "humanagent.h"
#include "cpuagent.h"
#include "starterdecklists.h"

using namespace l5r;

int main(int argc, char *argv[])
{
   //std::cout << "Neural Network Test" << std::endl;

   GamestateEncoder encoder;
   PolicyEncoder polEncoder;

   std::cout << "L5R Game simulator" << std::endl;

   std::string name;
   std::cout << "Name:";
   std::cin >> name;

   int i=1;
   int decknum=0;
   for(auto d: l5r::decklists)
   {
      std::cout << "[" << i++ << ".] " << d.getName() << std::endl;
   }
   std::cout << "Choose your deck: ";
   std::cin >> decknum;

   std::unique_ptr<l5r::agent> me = std::make_unique<l5r::cpuagent>(name, l5r::decklists[decknum-1]);

   std::cout << "Choose cpu deck: ";
   std::cin >> decknum;

   std::unique_ptr<l5r::agent> cpu = std::make_unique<l5r::cpuagent>("cpu", l5r::decklists[decknum-1]);

   l5r::engine game(std::move(me), std::move(cpu)); 

   gamestate gs = game.getGameState();
   double *arr;
   encoder.setupMap(&gs);
   polEncoder.setupMap(&gs);
   int layerSize=encoder.getTotalSize();
   int outLayerSize=polEncoder.getTotalSize();
   std::cout << "Total layer size is " << layerSize << std::endl;
   std::cout << "Output layer size is " << outLayerSize << std::endl;
   arr = new double[layerSize];
   encoder.encode(&gs, arr, layerSize);
   GameGraph fiverings(5, 0.01);
 
   GameSession sampleSession(&fiverings);

   fiverings.init(&sampleSession);

   double result;
   double resultpolicy[outLayerSize];
   fiverings.compute(&sampleSession, arr, layerSize, &result, resultpolicy, outLayerSize);

   std::cout << "result=" << result << std::endl;

   for(int i=0;i < outLayerSize; i++)
   {
      std::cout << resultpolicy[i] << " ";
   }
   std::cout << std::endl;

   delete[] arr;


//   encoder.validateCards(&gs);

   return 0;
}
