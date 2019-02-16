#include <stdio.h>
#include <string.h>
#include "tfgraph.h"
#include "tfsession.h"
#include "doubletensor.h"
#include "constop.h"
#include "addop.h"
#include "matmulop.h"
#include "floattensor.h"
#include "int32tensor.h"
#include "truncatednormalop.h"
#include "variable.h"
#include "assignop.h"
#include "booltensor.h"
#include "placeholder.h"
#include "mean.h"
#include "biasadd.h"
#include "squareddifference.h"
#include "gradients.h"
#include "relu.h"
#include "sigmoid.h"
#include "inputlayer.h"
#include "denselayer.h"
#include <tensorflow/c/c_api.h>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());

   TfGraph g;

   // start nnet graphs

   InputLayer il(&g, 5, 1, "input");

   DenseLayer dl(&g, 4, &il, ActivationType::RELU, "hidden1");

   DenseLayer dl2(&g, 3, &dl, ActivationType::RELU, "hidden2");

   DenseLayer dl3(&g, 2, &dl, ActivationType::RELU, "hidden3");

   DenseLayer dl4(&g, 1, &dl, ActivationType::SIGMOID, "hidden4");

   double inputdata[] = {1.0, 1.0, 0.0, 0.0, 0.0};
   const int64_t inputdims[] = {1, 5};

   DoubleTensor inputtensor(inputdims, 2, inputdata);
   DoubleTensor weights1, weights2,weights3, weights4;
   DoubleTensor biases1, biases2, biases3, biases4;
   DoubleTensor output2;

   TfSession sess4(&g);
   std::list<TfOperation*> wlist = {dl.getWeightInitializer(),
                                 dl2.getWeightInitializer(),
                                 dl3.getWeightInitializer(),
                                 dl4.getWeightInitializer()};
   std::list<TfOperation*> blist = {dl.getBiasInitializer(),
                                 dl2.getBiasInitializer(),
                                 dl3.getBiasInitializer(),
                                 dl4.getBiasInitializer()};
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptytensor;
   // initial weights
   sess4.run(empty, emptytensor, empty, emptytensor, wlist);
   // initialize biases
   sess4.run(empty, emptytensor, empty, emptytensor, blist);

   std::list<TfOperation*> varlist = {dl.getWeights(),
                                       dl2.getWeights(),
                                       dl3.getWeights(),
                                       dl4.getWeights(),
                                       dl.getBiases(),
                                       dl2.getBiases(),
                                       dl3.getBiases(),
                                       dl4.getBiases()};
   std::list<Tensor*> outlist = {&weights1,
                                 &weights2,
                                 &weights3,
                                 &weights4,
                                 &biases1,
                                 &biases2,
                                 &biases3,
                                 &biases4};

   // get weights and biases
   sess4.run(empty, emptytensor, varlist, outlist, empty);

   printf("weights1=\n");
   weights1.print();
   printf("weights2=\n");
   weights2.print();
   printf("weights3=\n");
   weights3.print();
   printf("weights4=\n");
   weights4.print();
   printf("biases1=\n");
   biases1.print();
   printf("biases2=\n");
   biases2.print();
   printf("biases3=\n");
   biases3.print();
   printf("biases4=\n");
   biases4.print();

   std::list<TfOperation*> inputOps={ &il };
   std::list<Tensor*> inputTensor = { &inputtensor };
   
   std::list<TfOperation*> outputOps= {&dl4};
   std::list<Tensor*> outputTensor = {&output2};
   sess4.run(inputOps, inputTensor, outputOps, outputTensor, empty);
   printf("result=\n");
   output2.print();
   //sess4.run(&il, &inputtensor, &sig, &t11, NULL);
   return 0;
}
