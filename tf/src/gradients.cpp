#include "gradients.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

Gradients::Gradients(TfGraph *g, TfOperation *x, TfOperation *out, const char* name) : TfOperation(g->getGraph())
{
//  TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "MatMul", name);
  TF_Status *status = TF_NewStatus();
  TF_Output outgrads;
  TF_Output inputs[2];
  inputs[0].oper=(TF_Operation*)x->getOp();
  inputs[0].index=0;
  inputs[1].oper=(TF_Operation*)out->getOp();
  inputs[1].index=0;
  TF_AddGradients(g->getGraph(), &inputs[0], 1, &inputs[1], 1, NULL, status, &outgrads);
  this->op = (TF_Operation*)outgrads.oper;
 // TF_AddInput(desc, inputs[0]);
 // TF_AddInput(desc, inputs[1]);
  //this->op = TF_FinishOperation(desc, status);
  printf("%s\n", TF_Message(status));
  TF_DeleteStatus(status);
}

Gradients::~Gradients()
{
}
