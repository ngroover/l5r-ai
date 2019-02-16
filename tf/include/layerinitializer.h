#ifndef _LAYER_INITIALIZER_H_
#define _LAYER_INITIALIZER_H_

#include <list>

class DenseLayer;
class TfSession;
class LayerInitializer
{
   public:
      LayerInitializer();
      ~LayerInitializer();

      void addLayer(DenseLayer *layer);

      void init(TfSession *session);
   private:
      std::list<DenseLayer*> layerList;
};

#endif // _LAYER_INITIALIZER_H_
