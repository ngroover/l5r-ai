#include "variable.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

Variable::Variable(TfGraph *g, TF_DataType dtype, const int64_t* dims, int dims_size, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Variable", name);
  TF_Status *status = TF_NewStatus();
  if(dims_size != 0)
  {
     TF_SetAttrShape(desc, "shape", dims, dims_size);
  }
  TF_SetAttrType(desc, "dtype", dtype);
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

Variable::~Variable()
{
}
