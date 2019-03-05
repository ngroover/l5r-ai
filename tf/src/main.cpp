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
#include "stringtensor.h"
#include "saveop.h"
#include "restoreop.h"
#include <tensorflow/c/c_api.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

int main() {
   printf("TensorFlow C library version %s\n", TF_Version());
   srand(time(NULL));

   TfGraph g;

   // start nnet graphs

   LayerInitializer layerinit;

   InputLayer il(&g, 5, 5, "input");
   InputLayer il2(&g, 5, 1, "inf_input");

   DenseLayer dl(&g, 4, &il, ActivationType::RELU, "hidden1");
   layerinit.addLayer(&dl);
   // inference layer
   DenseLayer dl_inf(&g, &il2, &dl, ActivationType::RELU, "inf_hidden1");

   DenseLayer dl2(&g, 3, &dl, ActivationType::RELU, "hidden2");
   layerinit.addLayer(&dl2);
   // inference layer
   DenseLayer dl2_inf(&g, &dl_inf, &dl2, ActivationType::RELU, "inf_hidden2");

   DenseLayer dl3(&g, 2, &dl2, ActivationType::RELU, "hidden3");
   layerinit.addLayer(&dl3);
   // inference layer
   DenseLayer dl3_inf(&g, &dl2_inf, &dl3, ActivationType::RELU, "inf_hidden3");

   DenseLayer dl4(&g, 1, &dl3, ActivationType::SIGMOID, "hidden4");
   layerinit.addLayer(&dl4);
   // inference layer
   DenseLayer dl4_inf(&g, &dl3_inf, &dl4, ActivationType::SIGMOID, "inf_hidden4");

   const int64_t outputdims[] = {5};
   Placeholder expected(&g, TF_DOUBLE, outputdims, 1, "expected");

   SquaredDifference sqdiff(&g, &dl4, &expected, "sqdiff");

   const int32_t meanAxisData[] = {0};
   const int64_t meanAxisDims[] = {1};
   Int32Tensor meanAxisTensor(meanAxisDims,1,meanAxisData);

   ConstOp meanAxis(&g, &meanAxisTensor, "meanAxis");

   Mean mean(&g, &sqdiff, &meanAxis, "mean");

   SGDOptimizer sgd(&g, 0.01, &mean, "optimizer");
   sgd.addLayer(&dl);
   sgd.addLayer(&dl2);
   sgd.addLayer(&dl3);
   sgd.addLayer(&dl4);

/*
   double inputdata[3190];
   for(int i=0;i<3190;i++)
   {
      inputdata[i] = (double)(rand() % 3);
   }
                         */
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

   // prefix
   std::list<std::string> restorestrList = {"./example"};
   const int64_t dims[] = {1};
   StringTensor restoreprefix(NULL, 0, restorestrList);
   ConstOp restoreprefixConst(&g, &restoreprefix, "restoreprefix");

   // tensor names
   std::list<std::string> restorestrList2 = {"hidden1_weights", "hidden1_biases",
                                       "hidden2_weights", "hidden2_biases",
                                       "hidden3_weights", "hidden3_biases",
                                       "hidden4_weights", "hidden4_biases"};
   const int64_t dims2[] = {8};
   StringTensor restoresomestr(dims2, 1, restorestrList2);
   ConstOp restoresomeStrConst(&g, &restoresomestr, "restoresomeStr");

   // shapes and slices
   std::list<std::string> restorestrList3 = {"", "", "", "", "", "", "", ""};
   StringTensor restoresomeshape(dims2, 1, restorestrList3);
   ConstOp restoresomeShapeConst(&g, &restoresomeshape, "restoresomeShape");

   std::list<TF_DataType> tlist = {TF_DOUBLE, TF_DOUBLE, TF_DOUBLE, TF_DOUBLE, TF_DOUBLE, TF_DOUBLE, TF_DOUBLE, TF_DOUBLE};
   
   std::cout << "Creating restore..." << std::endl;
   RestoreOp restoreop(&g, &restoreprefixConst, &restoresomeStrConst, &restoresomeShapeConst, tlist, "restoreop");

   // assign restore values
   AssignOp assweight1(&g, &restoreop, dl.getWeights(), "restoreassign1");

   AssignOp assweight2(&g, &restoreop, dl.getBiases(), 1, "restoreassign2");

   AssignOp assweight3(&g, &restoreop, dl2.getWeights(), 2, "restoreassign3");

   AssignOp assweight4(&g, &restoreop, dl2.getBiases(), 3, "restoreassign4");

   AssignOp assweight5(&g, &restoreop, dl3.getWeights(), 4, "restoreassign5");

   AssignOp assweight6(&g, &restoreop, dl3.getBiases(), 5, "restoreassign6");

   AssignOp assweight7(&g, &restoreop, dl4.getWeights(), 6, "restoreassign7");

   AssignOp assweight8(&g, &restoreop, dl4.getBiases(), 7, "restoreassign8");

   std::list<TfOperation*> empty;
   std::list<Tensor*> emptytensor;
   std::list<TfOperation*> restoreopList= {&restoreop, &assweight1, &assweight2, &assweight3, &assweight4, &assweight5, &assweight6, &assweight7, &assweight8};
   std::cout << "Restoring..." << std::endl;

   std::list<Tensor*> outlisttest = {&weights4};
   /*
                                 &weights2,
                                 &weights3,
                                 &weights4,
                                 &biases1,
                                 &biases2,
                                 &biases3,
                                 &biases4};
                                 */

   //sess4.run(empty, emptytensor, empty, emptytensor, restoreopList);
   std::cout << "Done restoring" << std::endl;
   /*
   printf("weights4=\n");
   weights4.print();
   */


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

   // get weights and biases
   //sess4.run(empty, emptytensor, varlist, outlist, empty);

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
   for(int i=0;i < 1000;i++)
   {
      sgd.optimize(&sess4, inputOps, inputTensor);
   }

   DoubleTensor mean_again;
   std::list<Tensor*> outlist_again2 = {&mean_again};

   sess4.run(inputOps, inputTensor, meanOutputOps, outlist_again2, empty);

   printf("mean_again=\n");
   mean_again.print();

   DoubleTensor final_result;;
   std::list<TfOperation*> outlist_op = {&dl4_inf};
   std::list<Tensor*> outlist_result = {&final_result};

   double inputdata_final[] = {1.0, 0.0, 1.0, 0.0, 0.0}; // 20
   const int64_t inputdims_final[] = {1, 5};
   DoubleTensor inputtensor_final(inputdims_final, 2, inputdata_final);
   std::list<TfOperation*> inputOps_final={ &il2 };
   std::list<Tensor*> inputTensor_final = { &inputtensor_final };

   // get an inference result
   sess4.run(inputOps_final, inputTensor_final, outlist_op, outlist_result, empty);

   printf("result_again=\n");
   final_result.print();

   // prefix
   std::list<std::string> strList = {"./example"};
   StringTensor prefix(NULL, 0, strList);
   ConstOp prefixConst(&g, &prefix, "prefix");

   // tensor names
   std::list<std::string> strList2 = {"hidden1_weights", "hidden1_biases",
                                       "hidden2_weights", "hidden2_biases",
                                       "hidden3_weights", "hidden3_biases",
                                       "hidden4_weights", "hidden4_biases"};
   StringTensor somestr(dims2, 1, strList2);
   ConstOp someStrConst(&g, &somestr, "someStr");

   // shapes and slices
   std::list<std::string> strList3 = {"", "", "", "", "", "", "", ""};
   StringTensor someshape(dims2, 1, strList3);
   ConstOp someShapeConst(&g, &someshape, "someShape");

   // tensors
   /*
   std::list<std::string> strList4 = {"tensor_double"};
   StringTensor sometensor(NULL, 0, strList4);
   ConstOp someTensorConst(&g, &sometensor, "someTensor");
   */
   std::list<TfOperation*> tops = {dl.getWeights(), dl.getBiases(),
                                    dl2.getWeights(), dl2.getBiases(),
                                    dl3.getWeights(), dl3.getBiases(),
                                    dl4.getWeights(), dl4.getBiases()};

   SaveOp save(&g, &prefixConst, &someStrConst, &someShapeConst, tops, "saveop");

   std::list<TfOperation*> saveopList= {&save};
   std::cout << "Saving..." << std::endl;
   sess4.run(empty, emptytensor, empty, emptytensor, saveopList);

   return 0;
}
