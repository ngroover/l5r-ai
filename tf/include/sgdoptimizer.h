#ifndef _SGD_OPTIMIZER_H_
#define _SGD_OPTIMIZER_H_

#include <list>

class DenseLayer;
class TfSession;
class DoubleTensor;
class ConstOp;
class TfOperation;
class Tensor;
class TfGraph;
class SGDOptimizer
{
   public:
      SGDOptimizer(TfGraph *g, double learningRate, TfOperation *optimizer);
      ~SGDOptimizer();

      void addLayer(DenseLayer *layer);

      void optimize(TfSession *session, std::list<TfOperation*> inputOps, std::list<Tensor*> inputTensors);

   private:
      int layerNum;
      std::list<TfOperation*> gradients;

      std::list<TfOperation*> gradientAppliers;

      DoubleTensor *lrtensor;
      ConstOp *lrconst;

      TfOperation *optimizer;
      TfGraph *g;
};

#endif // _SGD_OPTIMIZER_H_
