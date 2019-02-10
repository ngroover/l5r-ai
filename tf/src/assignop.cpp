#include "assignop.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

AssignOp::AssignOp(TfGraph *g, TfOperation *dest, TfOperation *src, const char* name) : TfOperation(g->getGraph())
{
  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Assign", name);
  TF_Status *status = TF_NewStatus();
  TF_Output inputs[2];
  inputs[0].oper=(TF_Operation*)src->getOp();
  inputs[0].index=0;
  inputs[1].oper=(TF_Operation*)dest->getOp();
  inputs[1].index=0;
  TF_AddInput(desc, inputs[0]);
  TF_AddInput(desc, inputs[1]);
  this->op = TF_FinishOperation(desc, status);
  TF_DeleteStatus(status);
}

AssignOp::~AssignOp()
{
}
