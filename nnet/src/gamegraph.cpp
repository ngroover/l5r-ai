#include "gamegraph.h"
#include "tfgraph.h"
#include "layerinitializer.h"
#include "tensor.h"
#include "gamesession.h"
#include "doubletensor.h"
#include "inputlayer.h"
#include "denselayer.h"
#include "sgdoptimizer.h"
#include "mean.h"
#include "squareddifference.h"
#include "int32tensor.h"
#include "constop.h"
#include "placeholder.h"
#include <list>

using namespace l5r;

const int GameGraph::input_size = 638;

GameGraph::GameGraph(int batchSize, int learningRate)
{
   this->batchSize = batchSize;

   // placeholder input
   training_input = new InputLayer(&g, input_size, batchSize, "training_input");
   inference_input = new InputLayer(&g, input_size, 1, "inference_input");

   // expected value placeholder
   const int64_t outputdims[] = {batchSize};
   expected = new Placeholder(&g, TF_DOUBLE, outputdims, 1, "expected");

   // hidden layer
   hidden1 = new DenseLayer(&g, 200, training_input, ActivationType::RELU, "hidden1");
   layerinit.addLayer(hidden1);
   DenseLayer inf_hidden1(&g, inference_input, hidden1, ActivationType::RELU, "inf_hidden1");

   // output layer
   output = new DenseLayer(&g, 1, hidden1, ActivationType::SIGMOID, "output");
   layerinit.addLayer(output);
   inference_output = new DenseLayer(&g, &inf_hidden1, output, ActivationType::SIGMOID, "inference_output");

   // square difference
   SquaredDifference sqdiff(&g, output, expected, "sqdiff");

   // mean
   const int32_t meanAxisData[] = {0};
   const int64_t meanAxisDims[] = {1};
   Int32Tensor meanAxisTensor(meanAxisDims,1,meanAxisData);

   ConstOp meanAxis(&g, &meanAxisTensor, "meanAxis");

   Mean mean(&g, &sqdiff, &meanAxis, "mean");

   // gradient descent optimizer
   optimizer = new SGDOptimizer(&g, learningRate, &mean);
   optimizer->addLayer(hidden1);
   optimizer->addLayer(output);
}

GameGraph::~GameGraph()
{
   delete inference_input;
   delete expected;
   delete inference_output;
   delete optimizer;
   delete hidden1;
   delete output;
}

void GameGraph::init(GameSession *session)
{
   layerinit.init(session->getSession());
}

void GameGraph::compute(GameSession *session, double *input, int size, double *valueOutput)
{
   if( size != input_size )
   {
      printf("Invalid input size of %d\n", size);
      return;
   }

   // output tensor
   DoubleTensor outputtensor;

   // input tensor
   const int64_t input_dims[] = {1, input_size};
   DoubleTensor inputtensor(input_dims, 2, input);

   // input lists
   std::list<TfOperation*> inputOps={ inference_input };
   std::list<Tensor*> inputtensor_list = { &inputtensor };

   // output lists
   std::list<TfOperation*> outputOps = {inference_output};
   std::list<Tensor*> outtensor_list = {&outputtensor};

   // empty op list
   std::list<TfOperation*> empty;

   // run the session
   session->getSession()->run(inputOps, inputtensor_list, outputOps, outtensor_list, empty);

   // copy value to output
   outputtensor.copyTo(valueOutput, 1);
}

void GameGraph::train(GameSession *session, double *input, int inputSize, double *valueOutput, int outputSize)
{
   if( inputSize != (input_size*batchSize) || 
      outputSize != (batchSize))
   {
      printf("Invalid input size or output size (%d %d)\n", inputSize, outputSize);
      return;
   }

   // input tensors
   const int64_t input_dims[] = {batchSize, input_size};
   const int64_t expected_input_dims[] = {batchSize, 1};
   DoubleTensor inputtensor(input_dims, 2, input);
   DoubleTensor expectedtensor(expected_input_dims, 2, valueOutput);

   // input lists
   std::list<TfOperation*> inputOps={ training_input, expected};
   std::list<Tensor*> inputtensor_list = { &inputtensor, &expectedtensor };

   // train
   optimizer->optimize(session->getSession(), inputOps, inputtensor_list);
}

TfGraph *GameGraph::getGraph()
{
   return &g;
}
