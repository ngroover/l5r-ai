#include "constop.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

ConstOp::ConstOp(TfGraph *g, DoubleTensor *t, std::string name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Const", name.c_str());
  TF_Status *status = TF_NewStatus();
  TF_SetAttrTensor(desc, "value", t->tensor, status);
  TF_SetAttrType(desc, "dtype", TF_TensorType(t->tensor));
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

ConstOp::~ConstOp()
{
}
