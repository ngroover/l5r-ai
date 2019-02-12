#include "layer.h"
#include "doubletensor.h"
#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

Layer::Layer(TfGraph *g, int layerSize):layerSize(layerSize), TfOperation(g->getGraph())
{
}

Layer::~Layer()
{
}

int Layer::getSize()
{
   return layerSize;
}

