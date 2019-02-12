#include "inputlayer.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include "placeholder.h"
#include "string.h"
#include <tensorflow/c/c_api.h>

InputLayer::InputLayer(TfGraph *g, int layerSize, int batchSize, const char* name): Layer(g, layerSize)
{
   const int64_t dims[] = {batchSize, layerSize};
   strcpy(this->name, name);
   strcat(this->name, "_placeholder");
   Placeholder ph(g, TF_DOUBLE, dims, 2, this->name);
   this->op = ph.getOp();
}

InputLayer::~InputLayer()
{
}

