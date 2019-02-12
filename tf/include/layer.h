#ifndef _LAYER_H_
#define _LAYER_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class Layer : public TfOperation
{
   public:
      Layer(TfGraph *g,int layerSize);
      ~Layer();

      int getSize();
   protected:
      int layerSize;
};

#endif // _LAYER_H_
