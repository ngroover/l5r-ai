#include "addop.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

AddOp::AddOp(TfGraph *g, TfOperation *x, TfOperation *y, const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "AddN", name);
   TF_Status *status = TF_NewStatus();
   TF_Output inputs[2];
   inputs[0].oper=(TF_Operation*)x->getOp();
   inputs[0].index=0;
   inputs[1].oper=(TF_Operation*)y->getOp();
   inputs[1].index=0;
   TF_AddInputList(desc, inputs, 2);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

AddOp::~AddOp()
{
}
