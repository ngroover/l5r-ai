#include "saveop.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

SaveOp::SaveOp(TfGraph *g, TfOperation *prefix, TfOperation *tensorName, TfOperation *shapes, std::list<TfOperation *> tensors, const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "SaveV2", name);
   TF_Status *status = TF_NewStatus();
   TF_Output inputs[3];
   inputs[0].oper=(TF_Operation*)prefix->getOp();
   inputs[0].index=0;
   inputs[1].oper=(TF_Operation*)tensorName->getOp();
   inputs[1].index=0;
   inputs[2].oper=(TF_Operation*)shapes->getOp();
   inputs[2].index=0;
   TF_Output inputlist[tensors.size()];
   int index=0;
   for( auto t : tensors)
   {
      inputlist[index].oper=(TF_Operation*)t->getOp();
      inputlist[index++].index=0;
   }
   TF_AddInput(desc, inputs[0]);
   TF_AddInput(desc, inputs[1]);
   TF_AddInput(desc, inputs[2]);
   TF_AddInputList(desc, inputlist, tensors.size());
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

SaveOp::~SaveOp()
{
}
