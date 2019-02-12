#ifndef _INPUT_LAYER_H_
#define _INPUT_LAYER_H_

#include "tfoperation.h"
#include "layer.h"
#include <string>

class TfGraph;
class DoubleTensor;
class InputLayer : public Layer
{
   public:
      InputLayer(TfGraph *g, int layerSize, int batchSize, const char* name);
      ~InputLayer();
   private:
      char name[64];
};

#endif // _INPUT_LAYER_H_
