#include "denselayer.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include "variable.h"
#include "matmulop.h"
#include "relu.h"
#include "sigmoid.h"
#include "truncatednormalop.h"
#include "parameterizedtruncatednormal.h"
#include "string.h"
#include "int32tensor.h"
#include "constop.h"
#include "assignop.h"
#include "biasadd.h"
#include "sigmoid.h"
#include "zeroslike.h"
#include <tensorflow/c/c_api.h>

DenseLayer::DenseLayer(TfGraph *g, int layerSize, Layer *previousLayer, ActivationType activation, const char* name) : Layer(g, layerSize)
{
   previousLayerSize = previousLayer->getSize();
   const int64_t dims[] = {previousLayerSize, layerSize};
   const int64_t biasdims[] = {layerSize};

   // this dense layer owns the variables so deallocate them upon destructor
   ownVars = true;

   // create weights
   strcpy(this->name, name);
   strcat(this->name, "_weights");
   weights = new Variable(g, TF_DOUBLE, dims, 2, this->name);

   // create bias
   strcpy(this->name, name);
   strcat(this->name, "_biases");
   bias = new Variable(g, TF_DOUBLE, biasdims, 1, this->name);

   // truncated normal size
   const int32_t dims32[] = {previousLayerSize, layerSize};
   const double biasdims32[layerSize] = {0};
   const int64_t sizeDim[] = {2};
   const int64_t biasSizeDim[] = {layerSize};
   const int64_t singleSize[] = {1};
   const double mean = 0.0;
   const double stdev = 0.20;
   const double maxval = 0.20;
   const double minval = -0.20;

   // mean of normal distribution
   DoubleTensor meanTensor(singleSize, 1, &mean);
   strcpy(this->name, name);
   strcat(this->name, "_normalmean");
   ConstOp normalmean(g, &meanTensor, this->name);

   // stdev of normal distribution
   DoubleTensor stdevTensor(singleSize, 1, &stdev);
   strcpy(this->name, name);
   strcat(this->name, "_normalstdev");
   ConstOp normalstdev(g, &stdevTensor, this->name);

   // minval of normal distribution
   DoubleTensor minvalTensor(singleSize, 1, &minval);
   strcpy(this->name, name);
   strcat(this->name, "_normalminval");
   ConstOp normalminval(g, &minvalTensor, this->name);

   // maxval of normal distribution
   DoubleTensor maxvalTensor(singleSize, 1, &maxval);
   strcpy(this->name, name);
   strcat(this->name, "_normalmaxval");
   ConstOp normalmaxval(g, &maxvalTensor, this->name);

   // weights size
   Int32Tensor weightSize(sizeDim, 1, dims32);
   strcpy(this->name, name);
   strcat(this->name, "_weightsconst");
   ConstOp weightSizeConst(g, &weightSize, this->name);

   // bias size
   DoubleTensor biasSize(biasSizeDim, 1, biasdims32);
   strcpy(this->name, name);
   strcat(this->name, "_biasconst");
   ConstOp biasSizeConst(g, &biasSize, this->name);

   // weights distribution
   strcpy(this->name, name);
   strcat(this->name, "_weightdist");
   ParameterizedTruncatedNormal weightsNormal(g, &weightSizeConst, &normalmean, &normalstdev, &normalminval, &normalmaxval, TF_DOUBLE, this->name);
   // non-parameterized normal distribution
   //TruncatedNormalOp weightsNormal(g, &weightSizeConst, TF_DOUBLE, this->name);

   // bias distribution
   strcpy(this->name, name);
   strcat(this->name, "_biasdist");
   ZerosLike biasNormal(g, &biasSizeConst, TF_DOUBLE, this->name);

   // weight assignment
   strcpy(this->name, name);
   strcat(this->name, "_assignweights");
   weightAssignment = new AssignOp(g, &weightsNormal,weights, this->name);

   // bias assignment
   strcpy(this->name, name);
   strcat(this->name, "_assignbias");
   biasAssignment = new AssignOp(g, &biasNormal,bias, this->name);

   initialize(g, previousLayer, activation, name);

   strcpy(this->name, name);
}

DenseLayer::DenseLayer(TfGraph *g, Layer *previousLayer, DenseLayer *parametersLayer, ActivationType activation, const char *name): Layer(g, parametersLayer->getSize())
{
   ownVars = false;
   weights = parametersLayer->getWeights();
   bias = parametersLayer->getBiases();

   initialize(g, previousLayer, activation, name);
   strcpy(this->name, name);
}

void DenseLayer::initialize(TfGraph *g, Layer *previousLayer, ActivationType activation, const char *name)
{
   // matrix multiply
   strcpy(this->name, name);
   strcat(this->name, "_matmul");
   MatMulOp mm(g, previousLayer, weights, this->name);

   // add bias
   strcpy(this->name, name);
   strcat(this->name, "_addbias");
   BiasAdd ba(g, &mm, bias, this->name);

   // activation (relu or sigmoid)
   if( activation == ActivationType::RELU )
   {
      strcpy(this->name, name);
      strcat(this->name, "_relu");
      Relu relu(g, &ba, this->name);
      this->op = relu.getOp();
   }else if( activation == ActivationType::SIGMOID )
   {
      strcpy(this->name, name);
      strcat(this->name, "_sigmoid");
      Sigmoid sigmoid(g, &ba, this->name);
      this->op = sigmoid.getOp();
   }
   else
   {
      this->op = ba.getOp();
   }
}

DenseLayer::~DenseLayer()
{
   if(ownVars)
   {
      delete weights;
      delete bias;
      delete weightAssignment;
      delete biasAssignment;
   }
}

TfOperation *DenseLayer::getWeightInitializer()
{
   return weightAssignment;
}

TfOperation *DenseLayer::getBiasInitializer()
{
   return biasAssignment;
}

TfOperation *DenseLayer::getWeights()
{
   return weights;
}

TfOperation *DenseLayer::getBiases()
{
   return bias;
}

std::string DenseLayer::getWeightsName()
{
   std::string weightname = std::string(this->name) + "_weights";
   return weightname;
}

std::string DenseLayer::getBiasesName()
{
   std::string biasesname = std::string(this->name) + "_biases";
   return biasesname;
}
