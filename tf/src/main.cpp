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
#include "mean.h"
#include <tensorflow/c/c_api.h>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());

   TfGraph g;

   // start nnet graphs

   InputLayer il(&g, 5, 5, "input");

   DenseLayer dl(&g, 4, &il, ActivationType::RELU, "hidden1");

   DenseLayer dl2(&g, 3, &dl, ActivationType::RELU, "hidden2");

   DenseLayer dl3(&g, 2, &dl, ActivationType::RELU, "hidden3");

   DenseLayer dl4(&g, 1, &dl, ActivationType::SIGMOID, "hidden4");

   const int64_t outputdims[] = {5};
   Placeholder expected(&g, TF_DOUBLE, outputdims, 1, "expected");

   SquaredDifference sqdiff(&g, &dl4, &expected, "sqdiff");

   const int32_t meanAxisData[] = {0};
   const int64_t meanAxisDims[] = {1};
   Int32Tensor meanAxisTensor(meanAxisDims,1,meanAxisData);

   ConstOp meanAxis(&g, &meanAxisTensor, "meanAxis");

   Mean mean(&g, &sqdiff, &meanAxis, "mean");

   double inputdata[] = {1.0, 0.0, 1.0, 0.0, 0.0, // 20
                         1.0, 0.0, 0.0, 0.0, 0.0, // 16
                         1.0, 1.0, 0.0, 0.0, 0.0, // 30
                         1.0, 1.0, 1.0, 1.0, 0.0, // 23
                         1.0, 1.0, 1.0, 0.0, 1.0}; // 29
   const int64_t inputdims[] = {5, 5};

   double expecteddata[] = { 0.625, // 20
                             0.5, // 16
                             0.9375, // 30
                             0.71875, // 23
                             0.90625}; // 29
   const int64_t expecteddims[] = {1,1};

   DoubleTensor inputtensor(inputdims, 2, inputdata);
   DoubleTensor expectedtensor(expecteddims, 2, expecteddata);
   DoubleTensor weights1, weights2,weights3, weights4;
   DoubleTensor biases1, biases2, biases3, biases4;
   DoubleTensor output2;
   DoubleTensor lossoutput;
   DoubleTensor meanoutput;

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

   std::list<TfOperation*> inputOps={ &il , &expected};
   std::list<Tensor*> inputTensor = { &inputtensor, &expectedtensor};
   
   std::list<TfOperation*> outputOps= {&dl4};
   std::list<Tensor*> outputTensor = {&output2};
   sess4.run(inputOps, inputTensor, outputOps, outputTensor, empty);
   printf("result=\n");
   output2.print();

   std::list<TfOperation*> lossOutputOps= {&sqdiff};
   std::list<Tensor*> lossOutputTensor = {&lossoutput};
   sess4.run(inputOps, inputTensor, lossOutputOps, lossOutputTensor, empty);
   printf("loss=\n");
   lossoutput.print();
   std::list<TfOperation*> meanOutputOps= {&mean};
   std::list<Tensor*> meanOutputTensor = {&meanoutput};
   sess4.run(inputOps, inputTensor, meanOutputOps, meanOutputTensor, empty);
   printf("mean=\n");
   meanoutput.print();

   // compute gradients
   DoubleTensor dlgradstensor;
   Gradients dlgrad(&g, &mean, dl.getWeights(), "d1grads");
   std::list<TfOperation*> gradsOutputOps= {&dlgrad};
   std::list<Tensor*> gradsOutputTensor = {&dlgradstensor};
   sess4.run(inputOps, inputTensor, gradsOutputOps, gradsOutputTensor, empty);
   printf("grads=\n");
   dlgradstensor.print();
   return 0;
}
