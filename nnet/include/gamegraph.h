#ifndef _GAME_GRAPH_H_
#define _GAME_GRAPH_H_

#include "tfgraph.h"
#include "layerinitializer.h"
#include "tfsession.h"

class InputLayer;
class DenseLayer;
class SGDOptimizer;
class Placeholder;
namespace l5r
{
   class GameSession;
   class GameGraph
   {
      public:
         GameGraph(int batchSize, int learningRate);
         ~GameGraph();

         TfGraph *getGraph();

         void init(GameSession *session);

         void compute(GameSession *session, double *input, int size, double *valueOutput);

         void train(GameSession *session, double *input, int inputSize, double *valueOutput, int outputSize);
      private:
         static const int input_size;
         int batchSize;
         TfGraph g;
         LayerInitializer layerinit;

         InputLayer *inference_input, *training_input;
         DenseLayer *inference_output;
         DenseLayer *hidden1;
         DenseLayer *output;
         SGDOptimizer *optimizer;
         Placeholder *expected;
   };
};

#endif // _GAME_GRAPH_H_
