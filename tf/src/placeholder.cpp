#include "placeholder.h"
#include "tensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>
#include <string.h>

Placeholder::Placeholder(TfGraph *g, TF_DataType dtype, const int64_t* dims, int dims_size, const char* name) : TfOperation(g->getGraph())
{
   TF_OperationDescription* desc = TF_NewOperation(g->getGraph(), "Placeholder", name);
   TF_Status *status = TF_NewStatus();
   if(dims_size != 0)
   {
     TF_SetAttrShape(desc, "shape", dims, dims_size);
   }
   TF_SetAttrType(desc, "dtype", dtype);
   this->op = TF_FinishOperation(desc, status);
   if(strcmp(TF_Message(status), "") != 0)
   {
      printf("%s\n", TF_Message(status));
   }
   TF_DeleteStatus(status);
}

Placeholder::~Placeholder()
{
}
