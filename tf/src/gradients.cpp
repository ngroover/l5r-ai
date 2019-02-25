#include "gradients.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

Gradients::Gradients(TfGraph *g, TfOperation *x, TfOperation *out, const char* name) : TfOperation(g->getGraph())
{
   TF_Status *status = TF_NewStatus();
   TF_Output outgrads;
   TF_Output inputs[2];
   inputs[0].oper=(TF_Operation*)x->getOp();
   inputs[0].index=0;
   inputs[1].oper=(TF_Operation*)out->getOp();
   inputs[1].index=0;
   TF_AddGradients(g->getGraph(), &inputs[0], 1, &inputs[1], 1, NULL, status, &outgrads);
   this->op = (TF_Operation*)outgrads.oper;
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

Gradients::~Gradients()
{
}
