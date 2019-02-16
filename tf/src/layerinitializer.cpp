#include "layerinitializer.h"
#include "denselayer.h"
#include "tfsession.h"
#include "tfoperation.h"
#include <tensorflow/c/c_api.h>

LayerInitializer::LayerInitializer()
{
}

LayerInitializer::~LayerInitializer()
{
}

void LayerInitializer::addLayer(DenseLayer *layer)
{
   layerList.push_back(layer);
}

void LayerInitializer::init(TfSession *session)
{
   std::list<TfOperation*> initList;
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptyTensor;
   for(auto layer : layerList )
   {
      initList.push_back(layer->getWeightInitializer());
      initList.push_back(layer->getBiasInitializer());
   }
   session->run(empty, emptyTensor, empty, emptyTensor, initList);
}
