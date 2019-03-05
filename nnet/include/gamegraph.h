#ifndef _GAME_GRAPH_H_
#define _GAME_GRAPH_H_

#include "tfgraph.h"
#include "layerinitializer.h"
#include "tfsession.h"
#include <string>

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
         GameGraph(int batchSize, double learningRate);
         ~GameGraph();

         TfGraph *getGraph();

         // init weights randomly
         void init(GameSession *session);

         // restore from file
         bool load(GameSession *session, std::string name);

         // save network to file
         void save(GameSession *session, std::string name);

         void compute(GameSession *session, double *input, int size, double *valueOutput, double *policyOutput, int policySize);

         void train(GameSession *session, double *input, int inputSize, double *valueOutput, int outputSize, double *policyOutput, int policySize);

      private:
         static const int input_size;
         static const int policy_output_size;
         int batchSize;
         TfGraph g;
         LayerInitializer layerinit;

         InputLayer *inference_input, *training_input;
         DenseLayer *inference_output, *inference_output_policy;
         DenseLayer *hidden1;
         DenseLayer *output;
         DenseLayer *output_policy;
         SGDOptimizer *optimizer, *optimizer_policy;
         Placeholder *expected;
         Placeholder *expected_policy;
   };
};

#endif // _GAME_GRAPH_H_
