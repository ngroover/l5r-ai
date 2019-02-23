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
#include "layerinitializer.h"
#include "applygradientdescent.h"
#include "sgdoptimizer.h"
#include <tensorflow/c/c_api.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());
   srand(time(NULL));

   TfGraph g;

   // start nnet graphs

   LayerInitializer layerinit;

   InputLayer il(&g, 638, 5, "input");

   DenseLayer dl(&g, 200, &il, ActivationType::SIGMOID, "hidden1");
   layerinit.addLayer(&dl);

   //DenseLayer dl2(&g, 200, &dl, ActivationType::RELU, "hidden2");
   //layerinit.addLayer(&dl2);

   //DenseLayer dl3(&g, 50, &dl2, ActivationType::RELU, "hidden3");
   //layerinit.addLayer(&dl3);

   DenseLayer dl4(&g, 1, &dl, ActivationType::SIGMOID, "hidden4");
   layerinit.addLayer(&dl4);

   const int64_t outputdims[] = {5};
   Placeholder expected(&g, TF_DOUBLE, outputdims, 1, "expected");

   SquaredDifference sqdiff(&g, &dl4, &expected, "sqdiff");

   const int32_t meanAxisData[] = {0};
   const int64_t meanAxisDims[] = {1};
   Int32Tensor meanAxisTensor(meanAxisDims,1,meanAxisData);

   ConstOp meanAxis(&g, &meanAxisTensor, "meanAxis");

   Mean mean(&g, &sqdiff, &meanAxis, "mean");

   SGDOptimizer sgd(&g, 0.01, &mean);
   sgd.addLayer(&dl);
   //sgd.addLayer(&dl2);
   //sgd.addLayer(&dl3);
   sgd.addLayer(&dl4);

   double inputdata[3190];
   for(int i=0;i<3190;i++)
   {
      inputdata[i] = (double)(rand() % 3);
   }
   /*
   double inputdata[] = {1.0, 0.0, 1.0, 0.0, 0.0, // 20
                         1.0, 0.0, 0.0, 0.0, 0.0, // 16
                         1.0, 1.0, 0.0, 0.0, 0.0, // 30
                         1.0, 1.0, 1.0, 1.0, 0.0, // 23
                         1.0, 1.0, 1.0, 0.0, 1.0}; // 29
                         */
   const int64_t inputdims[] = {5, 638};

   double expecteddata[] = { 0.625, // 20
                             0.5, // 16
                             0.9375, // 30
                             0.71875, // 23
                             0.90625}; // 29
   const int64_t expecteddims[] = {5,1};

   DoubleTensor inputtensor(inputdims, 2, inputdata);
   DoubleTensor expectedtensor(expecteddims, 2, expecteddata);
   DoubleTensor weights1, weights2,weights3, weights4;
   DoubleTensor biases1, biases2, biases3, biases4;
   DoubleTensor output2;
   DoubleTensor lossoutput;
   DoubleTensor meanoutput;

   TfSession sess4(&g);
   layerinit.init(&sess4);

   std::list<TfOperation*> varlist = {dl4.getWeights()};
   /*
                                       dl2.getWeights(),
                                       dl3.getWeights(),
                                       dl4.getWeights(),
                                       dl.getBiases(),
                                       dl2.getBiases(),
                                       dl3.getBiases(),
                                       dl4.getBiases()};
                                       */
   std::list<Tensor*> outlist = {&weights4};
   /*
                                 &weights2,
                                 &weights3,
                                 &weights4,
                                 &biases1,
                                 &biases2,
                                 &biases3,
                                 &biases4};
*/
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptytensor;

   // get weights and biases
   sess4.run(empty, emptytensor, varlist, outlist, empty);

/*
   printf("weights4=\n");
   weights4.print();
   */
   /*
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
   */

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

/*
   // compute gradients
   DoubleTensor dlgradstensor;
   Gradients dlgrad(&g, &mean, dl.getWeights(), "d1grads");
   std::list<TfOperation*> gradsOutputOps= {&dlgrad};
   std::list<Tensor*> gradsOutputTensor = {&dlgradstensor};
   sess4.run(inputOps, inputTensor, gradsOutputOps, gradsOutputTensor, empty);
   printf("grads=\n");
   dlgradstensor.print();

   double learningratedata[] = {0.1};
   const int64_t learningratedims[] = {5, 4};
   DoubleTensor lrtensor(NULL, 0, learningratedata);

   ConstOp lrconst(&g, &lrtensor, "lr_rate");
   
   // apply gradient descent
   ApplyGradientDescent agd(&g, dl.getWeights(), &lrconst, &dlgrad, "apply_gd");

   std::list<TfOperation*> gd_list = {&agd};

   sess4.run(inputOps, inputTensor, varlist, outlist_again, gd_list);

   printf("weights_again=\n");
   weights_again.print();
   */
   for(int i=0;i < 10000;i++)
   {
      sgd.optimize(&sess4, inputOps, inputTensor);
   }

   DoubleTensor mean_again;
   std::list<Tensor*> outlist_again2 = {&mean_again};

   sess4.run(inputOps, inputTensor, meanOutputOps, outlist_again2, empty);

   printf("mean_again=\n");
   mean_again.print();

   // get weights and biases
   sess4.run(empty, emptytensor, varlist, outlist, empty);

/*
   printf("weights4=\n");
   weights4.print();
   */

   return 0;
}
