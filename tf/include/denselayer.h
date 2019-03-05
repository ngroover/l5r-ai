#ifndef _DENSE_LAYER_H_
#define _DENSE_LAYER_H_

#include "tfoperation.h"
#include "layer.h"
#include <string>

class TfGraph;
class DoubleTensor;

enum class ActivationType
{
   RELU,
   SIGMOID
};

class DenseLayer : public Layer
{
   public:
      DenseLayer(TfGraph *g, int layerSize, Layer *previousLayer, ActivationType activation, const char* name);

      // Create a layer in which it shares weights and biases from parametersLayer but has it's own previousLayer
      DenseLayer(TfGraph *g, Layer *previousLayer, DenseLayer *parametersLayer, ActivationType activation, const char *name);

      ~DenseLayer();

      TfOperation *getWeightInitializer();
      TfOperation *getBiasInitializer();
      TfOperation *getWeights();
      TfOperation *getBiases();

      std::string getWeightsName();
      std::string getBiasesName();

   private:
      char name[64];
      int previousLayerSize;
      bool ownVars;
      TfOperation *weights;
      TfOperation *bias;
      TfOperation *weightAssignment;
      TfOperation *biasAssignment;

      void initialize(TfGraph *g, Layer *previousLayer, ActivationType activation, const char *name);
};

#endif // _DENSE_LAYER_H_
