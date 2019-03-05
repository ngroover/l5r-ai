#include "assignop.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

AssignOp::AssignOp(TfGraph *g, TfOperation *val, TfOperation *var, const char* name) : TfOperation(g->getGraph())
{
   initialize(g, val, var, 0, name);
}

AssignOp::AssignOp(TfGraph *g, TfOperation *val, TfOperation *var, int index, const char* name) : TfOperation(g->getGraph())
{
   initialize(g, val, var, index, name);
}

void AssignOp::initialize(TfGraph *g, TfOperation *val, TfOperation *var, int index, const char* name)
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Assign", name);
   TF_Status *status = TF_NewStatus();
   TF_Output inputs[2];
   inputs[0].oper=(TF_Operation*)var->getOp();
   inputs[0].index=0;
   inputs[1].oper=(TF_Operation*)val->getOp();
   inputs[1].index=index;
   TF_AddInput(desc, inputs[0]);
   TF_AddInput(desc, inputs[1]);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

AssignOp::~AssignOp()
{
}
