#ifndef _GAME_GRAPH_H_
#define _GAME_GRAPH_H_

#include "tfgraph.h"
#include "layerinitializer.h"
#include "tfsession.h"

namespace l5r
{
   class GameGraph
   {
      public:
         GameGraph();
         ~GameGraph();

         void init(GameSession *session);

         void compute(double *input, int size);

         void train(double *input, int totalSize);
      private:
         const int input_size;
         TfGraph g;
         LayerInitializer layerinit;
   };
};

#endif // _GAME_GRAPH_H_
