#include "denselayer.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include "variable.h"
#include "matmulop.h"
#include "relu.h"
#include "sigmoid.h"
#include "truncatednormalop.h"
#include "string.h"
#include "int32tensor.h"
#include "constop.h"
#include "assignop.h"
#include <tensorflow/c/c_api.h>

DenseLayer::DenseLayer(TfGraph *g, int layerSize, Layer *previousLayer, const char* name) : Layer(g, layerSize)
{
   const int64_t dims[] = {previousLayer->getSize(), layerSize};
   printf("layer size is %d\n", layerSize);

   // create weights
   strcpy(this->name, name);
   strcat(this->name, "_weights");
   weights = new Variable(g, TF_DOUBLE, dims, 2, this->name);

   // matrix multiply
   strcpy(this->name, name);
   strcat(this->name, "_matmul");
   MatMulOp mm(g, previousLayer, weights, this->name);
   // activation (relu) TODO: sigmoid
   strcpy(this->name, name);
   strcat(this->name, "_relu");
   Relu relu(g, &mm, this->name);
   this->op = relu.getOp();

   // weights initializer (truncated normal)
   const int32_t dims32[] = {previousLayer->getSize(), layerSize};
   const int64_t sizeDim[] = {2};
   Int32Tensor normalSize(sizeDim, 1, dims32);
   strcpy(this->name, name);
   strcat(this->name, "_normalconst");
   ConstOp normalSizeConst(g, &normalSize, this->name);

   strcpy(this->name, name);
   strcat(this->name, "_normaldist");
   TruncatedNormalOp tn(g, &normalSizeConst, TF_DOUBLE, this->name);

   // assignment
   strcpy(this->name, name);
   strcat(this->name, "_assign");
   assignment = new AssignOp(g, &tn,weights, this->name);
}

DenseLayer::~DenseLayer()
{
   delete weights;
   delete assignment;
}

TfOperation *DenseLayer::getInitializer()
{
   return assignment;
}

TfOperation *DenseLayer::getWeights()
{
   return weights;
}

