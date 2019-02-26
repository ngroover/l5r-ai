#include "parameterizedtruncatednormal.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

ParameterizedTruncatedNormal::ParameterizedTruncatedNormal(TfGraph *g, TfOperation *inp, TfOperation *mean, TfOperation *stdev, TfOperation *minval, TfOperation *maxval, TF_DataType dtype, const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "ParameterizedTruncatedNormal", name);
   TF_Status *status = TF_NewStatus();
   TF_Output inputs[5];
   inputs[0].oper=(TF_Operation*)inp->getOp();
   inputs[0].index=0;
   inputs[1].oper=(TF_Operation*)mean->getOp();
   inputs[1].index=0;
   inputs[2].oper=(TF_Operation*)stdev->getOp();
   inputs[2].index=0;
   inputs[3].oper=(TF_Operation*)minval->getOp();
   inputs[3].index=0;
   inputs[4].oper=(TF_Operation*)maxval->getOp();
   inputs[4].index=0;
   TF_AddInput(desc, inputs[0]);
   TF_AddInput(desc, inputs[1]);
   TF_AddInput(desc, inputs[2]);
   TF_AddInput(desc, inputs[3]);
   TF_AddInput(desc, inputs[4]);
   TF_SetAttrType(desc, "dtype", dtype);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

ParameterizedTruncatedNormal::~ParameterizedTruncatedNormal()
{
}
