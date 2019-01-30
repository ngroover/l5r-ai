#include "constop.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

ConstOp::ConstOp(TfGraph *g, Tensor *t, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Const", name);
  TF_Status *status = TF_NewStatus();
  TF_SetAttrTensor(desc, "value", *t->getTensor(), status);
  TF_SetAttrType(desc, "dtype", TF_TensorType(*t->getTensor()));
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

ConstOp::~ConstOp()
{
}
