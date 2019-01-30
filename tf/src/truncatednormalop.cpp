#include "truncatednormalop.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

TruncatedNormalOp::TruncatedNormalOp(TfGraph *g, TfOperation *x, TF_DataType dtype, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "TruncatedNormal", name);
  TF_Status *status = TF_NewStatus();
  TF_Output inputs;
  inputs.oper=(TF_Operation*)x->getOp();
  inputs.index=0;
  TF_AddInput(desc, inputs);
  TF_SetAttrType(desc, "dtype", dtype);
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

TruncatedNormalOp::~TruncatedNormalOp()
{
}
