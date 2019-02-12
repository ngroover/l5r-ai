#ifndef _DENSE_LAYER_H_
#define _DENSE_LAYER_H_

#include "tfoperation.h"
#include "layer.h"
#include <string>

class TfGraph;
class DoubleTensor;
class DenseLayer : public Layer
{
   public:
      DenseLayer(TfGraph *g, int layerSize, Layer *previousLayer, const char* name);
      ~DenseLayer();

      TfOperation *getWeightInitializer();
      TfOperation *getBiasInitializer();
      TfOperation *getWeights();
      TfOperation *getBiases();
   private:
      char name[64];
      TfOperation *weights;
      TfOperation *bias;
      TfOperation *weightAssignment;
      TfOperation *biasAssignment;
};

#endif // _DENSE_LAYER_H_
