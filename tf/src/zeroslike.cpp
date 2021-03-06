#include "zeroslike.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

ZerosLike::ZerosLike(TfGraph *g, TfOperation *x, TF_DataType dtype, const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "ZerosLike", name);
   TF_Status *status = TF_NewStatus();
   TF_Output inputs;
   inputs.oper=(TF_Operation*)x->getOp();
   inputs.index=0;
   TF_AddInput(desc, inputs);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

ZerosLike::~ZerosLike()
{
}
