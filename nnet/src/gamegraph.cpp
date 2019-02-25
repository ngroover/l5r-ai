#include "gamegraph.h"
#include "tfgraph.h"
#include "layerinitializer.h"

using namespace l5r;

GameGraph::input_size = 638;

GameGraph::GameGraph(int batchSize, int learningRate)
{
   // placeholder input
   InputLayer training_input(&g, input_size, batchSize, "training_input");
   InputLayer inference_input(&g, input_size, 1, "inference_input");

   // expected value placeholder
   const int64_t outputdims[] = {batchSize};
   Placeholder expected(&g, TF_DOUBLE, outputdims, 1, "expected");

   // hidden layer
   DenseLayer hidden1(&g, 400, &il, ActivationType::RELU, "hidden1");
   layerinit.addLayer(&hidden1);
   DenseLayer inf_hidden1(&g, &inference_input, &hidden1, ActivationType::RELU, "inf_hidden1");

   // output layer
   DenseLayer output(&g, 1, &hidden1, ActivationType::SIGMOID, "hidden4");
   layerinit.addLayer(&output);
   DenseLayer inf_output(&g, &inf_hidden1, &output, ActivationType::SIGMOID, "inf_output");

   // square difference
   SquaredDifference sqdiff(&g, &output, &expected, "sqdiff");

   // mean
   const int32_t meanAxisData[] = {0};
   const int64_t meanAxisDims[] = {1};
   Int32Tensor meanAxisTensor(meanAxisDims,1,meanAxisData);

   ConstOp meanAxis(&g, &meanAxisTensor, "meanAxis");

   Mean mean(&g, &sqdiff, &meanAxis, "mean");

   // gradient descent optimizer
   SGDOptimizer sgd(&g, learningRate, &mean);
   sgd.addLayer(&hidden1);
   sgd.addLayer(&output);
}

~GameGraph::GameGraph()
{
}

void GameGraph::init(GameSession *session)
{
   layerinit.init(session);
}

void GameGraph::compute(GameSession *session, double *input, int size, double *valueOutput)
{
   if( size != input_size )
   {
      printf("Invalid input size of %d\n", size);
      return;
   }

   DoubleTensor output;
   std::list<TfOperation*> varlist = {inf_output};
   std::list<Tensor*> outlist = {&output};
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptytensor;
}

void GameGraph::train(double *input, int totalSize, double outputValue)
{
}
