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
#include <fstream>

using namespace l5r;

// TODO: dyamically update these
const int GameGraph::input_size = 1168;
const int GameGraph::policy_output_size = 255;

GameGraph::GameGraph(int batchSize, double learningRate)
{
   this->batchSize = batchSize;

   // placeholder input
   training_input = new InputLayer(&g, input_size, batchSize, "training_input");
   inference_input = new InputLayer(&g, input_size, 1, "inference_input");

   // expected value placeholder
   const int64_t outputdims[] = {batchSize};
   expected = new Placeholder(&g, TF_DOUBLE, outputdims, 1, "expected");

   // expected policy placeholder
   const int64_t outputpolicydims[] = {batchSize, policy_output_size};
   expected_policy = new Placeholder(&g, TF_DOUBLE, outputpolicydims, 2, "expected_policy");

   // hidden layer (shared)
   hidden1 = new DenseLayer(&g, 500, training_input, ActivationType::RELU, "hidden1");
   layerinit.addLayer(hidden1);
   DenseLayer inf_hidden1(&g, inference_input, hidden1, ActivationType::RELU, "inf_hidden1");

   // output layer (value)
   output = new DenseLayer(&g, 1, hidden1, ActivationType::SIGMOID, "output");
   layerinit.addLayer(output);
   inference_output = new DenseLayer(&g, &inf_hidden1, output, ActivationType::SIGMOID, "inference_output");

   // output layer (policy)
   output_policy = new DenseLayer(&g, policy_output_size, hidden1, ActivationType::SIGMOID, "output_policy");
   layerinit.addLayer(output_policy);
   inference_output_policy = new DenseLayer(&g, &inf_hidden1, output_policy, ActivationType::SIGMOID, "inference_output_policy");

   // square difference
   SquaredDifference sqdiff(&g, output, expected, "sqdiff");

   SquaredDifference sqdiff_policy(&g, output_policy, expected_policy, "sqdiff_policy");

   // mean
   const int32_t meanAxisData[] = {0};
   const int64_t meanAxisDims[] = {1};
   Int32Tensor meanAxisTensor(meanAxisDims,1,meanAxisData);

   ConstOp meanAxis(&g, &meanAxisTensor, "meanAxis");

   Mean mean(&g, &sqdiff, &meanAxis, "mean");

   Mean mean_policy(&g, &sqdiff_policy, &meanAxis, "mean_policy");

   // gradient descent optimizers
   optimizer = new SGDOptimizer(&g, learningRate, &mean, "value_optimizer");
   optimizer->addLayer(hidden1);
   optimizer->addLayer(output);
   optimizer_policy = new SGDOptimizer(&g, learningRate, &mean_policy, "policy_optimizer");
   optimizer_policy->addLayer(hidden1);
   optimizer_policy->addLayer(output_policy);
}

GameGraph::~GameGraph()
{
   delete inference_input;
   delete training_input;
   delete expected;
   delete expected_policy;
   delete inference_output_policy;
   delete inference_output;
   delete optimizer;
   delete optimizer_policy;
   delete hidden1;
   delete output;
}

void GameGraph::init(GameSession *session)
{
   layerinit.init(session->getSession());
}

bool GameGraph::load(GameSession *session, std::string name)
{
   // TODO: check data file too
   std::ifstream infile(name+".index");
   if(infile.good())
   {
      layerinit.load(&g, session->getSession(), name);
      return true;
   }
   return false;
}

void GameGraph::save(GameSession *session, std::string name)
{
   layerinit.save(&g, session->getSession(), name);
}

void GameGraph::compute(GameSession *session, double *input, int size, double *valueOutput, double *policyOutput, int policySize)
{
   if( size != input_size || policySize != policy_output_size )
   {
      printf("Invalid input size (gamestate=%d, policy=%d)\n", size, policySize);
      return;
   }

   // output tensor
   DoubleTensor outputvalue;
   DoubleTensor outputpolicy;

   // input tensor
   const int64_t input_dims[] = {1, input_size};
   DoubleTensor inputtensor(input_dims, 2, input);

   // input lists
   std::list<TfOperation*> inputOps={ inference_input };
   std::list<Tensor*> inputtensor_list = { &inputtensor };

   // output lists
   std::list<TfOperation*> outputOps = {inference_output, inference_output_policy};
   std::list<Tensor*> outtensor_list = {&outputvalue, &outputpolicy};

   // empty op list
   std::list<TfOperation*> empty;

   // run the session
   session->getSession()->run(inputOps, inputtensor_list, outputOps, outtensor_list, empty);

   // copy value to output
   outputvalue.copyTo(valueOutput, 1);

   // copy policy to output
   outputpolicy.copyTo(policyOutput, policySize);
}

void GameGraph::train(GameSession *session, double *input, int inputSize, double *valueOutput, int outputSize, double *policyOutput, int policySize)
{
   if( inputSize != (input_size*batchSize) || 
      outputSize != (batchSize) ||
      policySize != (policy_output_size*batchSize))
   {
      printf("Invalid input size, output size  or policy size (%d %d %d)\n", inputSize, outputSize, policySize);
      return;
   }

   // input tensors
   const int64_t input_dims[] = {batchSize, input_size};
   const int64_t expected_input_dims[] = {batchSize, 1};
   const int64_t expected_policy_input_dims[] = {batchSize, policy_output_size};
   DoubleTensor inputtensor(input_dims, 2, input);
   DoubleTensor expectedtensor(expected_input_dims, 2, valueOutput);
   DoubleTensor expectedpolicytensor(expected_policy_input_dims, 2, policyOutput);

   // input lists (value)
   std::list<TfOperation*> inputOps={ training_input, expected};
   std::list<Tensor*> inputtensor_list = { &inputtensor, &expectedtensor };

   // input lists (policy)
   std::list<TfOperation*> inputOps_policy={ training_input, expected_policy};
   std::list<Tensor*> inputtensor_list_policy = { &inputtensor, &expectedpolicytensor };

   // train value
   optimizer->optimize(session->getSession(), inputOps, inputtensor_list);

   // train policy
   optimizer_policy->optimize(session->getSession(), inputOps_policy, inputtensor_list_policy);
}

TfGraph *GameGraph::getGraph()
{
   return &g;
}
