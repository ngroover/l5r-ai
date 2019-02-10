#include "variableread.h"
#include "tensor.h"
#include "variable.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

VariableRead::VariableRead(TfGraph *g, Variable *v, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "ReadVariableOp", name);
  TF_Status *status = TF_NewStatus();
  TF_Output input;
  input.oper=(TF_Operation*)v->getOp();
  input.index=0;
  TF_AddInput(desc, input);
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

VariableRead::~VariableRead()
{
}
