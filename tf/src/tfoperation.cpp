#include "tfoperation.h"
#include <tensorflow/c/c_api.h>

TfOperation::TfOperation(TF_Graph *graph)
{
   this->graph = graph;
}

TfOperation::~TfOperation()
{
}
