#include "relu.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

Relu::Relu(TfGraph *g, TfOperation *x, const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Relu", name);
   TF_Status *status = TF_NewStatus();
   TF_Output input;
   input.oper=(TF_Operation*)x->getOp();
   input.index=0;
   TF_AddInput(desc, input);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

Relu::~Relu()
{
}
