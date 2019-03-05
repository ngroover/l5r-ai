#ifndef _LAYER_INITIALIZER_H_
#define _LAYER_INITIALIZER_H_

#include <list>
#include <string>

class DenseLayer;
class TfSession;
class RestoreOp;
class TfGraph;
class TfOperation;
class SaveOp;
class ConstOp;
class LayerInitializer
{
   public:
      LayerInitializer();
      ~LayerInitializer();

      void addLayer(DenseLayer *layer);

      void init(TfSession *session);

      void load(TfGraph *g, TfSession *session, std::string name);
      void save(TfGraph *g, TfSession *session, std::string name);
   private:
      std::list<DenseLayer*> layerList;

      RestoreOp *restore; 
      SaveOp *saveOp;
      std::list<TfOperation*> restoreList;

      // common ops for save and restore
      void createCommonOps(TfGraph *g, TfSession *session, std::string name);

      ConstOp *prefixConst;
      ConstOp *tensorNamesConst;
      ConstOp *shapesConst;
};

#endif // _LAYER_INITIALIZER_H_
