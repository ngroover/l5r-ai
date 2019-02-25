#include "applygradientdescent.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

ApplyGradientDescent::ApplyGradientDescent(TfGraph *g, TfOperation *var, TfOperation *lr, TfOperation *delta,const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "ApplyGradientDescent", name);
   TF_Status *status = TF_NewStatus();
   TF_Output inputs[3];
   inputs[0].oper=(TF_Operation*)var->getOp();
   inputs[0].index=0;
   inputs[1].oper=(TF_Operation*)lr->getOp();
   inputs[1].index=0;
   inputs[2].oper=(TF_Operation*)delta->getOp();
   inputs[2].index=0;
   TF_AddInput(desc, inputs[0]);
   TF_AddInput(desc, inputs[1]);
   TF_AddInput(desc, inputs[2]);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

ApplyGradientDescent::~ApplyGradientDescent()
{
}
