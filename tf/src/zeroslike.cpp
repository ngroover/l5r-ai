#include "zeroslike.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

ZerosLike::ZerosLike(TfGraph *g, TfOperation *x, TF_DataType dtype, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "ZerosLike", name);
  TF_Status *status = TF_NewStatus();
  TF_Output inputs;
  inputs.oper=(TF_Operation*)x->getOp();
  inputs.index=0;
  TF_AddInput(desc, inputs);
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

ZerosLike::~ZerosLike()
{
}
