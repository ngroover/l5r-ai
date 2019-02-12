#include "biasadd.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

BiasAdd::BiasAdd(TfGraph *g, TfOperation *x, TfOperation *y, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "BiasAdd", name);
  TF_Status *status = TF_NewStatus();
  TF_Output inputs[2];
  inputs[0].oper=(TF_Operation*)x->getOp();
  inputs[0].index=0;
  inputs[1].oper=(TF_Operation*)y->getOp();
  inputs[1].index=0;
  TF_AddInput(desc, inputs[0]);
  TF_AddInput(desc, inputs[1]);
  this->op = TF_FinishOperation(desc, status);
  printf("%s\n", TF_Message(status));
  TF_DeleteStatus(status);
}

BiasAdd::~BiasAdd()
{
}
