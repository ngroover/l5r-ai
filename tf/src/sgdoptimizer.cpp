#include "sgdoptimizer.h"
#include "denselayer.h"
#include "tfsession.h"
#include "doubletensor.h"
#include "constop.h"
#include "tfoperation.h"
#include <string>
#include "gradients.h"
#include "applygradientdescent.h"
#include <tensorflow/c/c_api.h>

SGDOptimizer::SGDOptimizer(TfGraph *g, double learningRate, TfOperation *optimizer)
{
   lrtensor = new DoubleTensor(NULL, 0, &learningRate);

   lrconst = new ConstOp(g, lrtensor, "lr_rate");
   this->optimizer = optimizer;
   layerNum=0;
   this->g = g;
}

SGDOptimizer::~SGDOptimizer()
{
   delete lrtensor;
   delete lrconst;
   for(auto grad: gradients)
   {
      delete grad;
   }
   for(auto appgrad: gradientAppliers)
   {
      delete appgrad;
   }
}

void SGDOptimizer::addLayer(DenseLayer *layer)
{
   std::string prefix = "layer" + std::to_string(layerNum++);
   std::string weightName = prefix+"_weight";
   std::string biasName = prefix+"_bias";

   Gradients *wgrad = new Gradients(g, optimizer, layer->getWeights(), (weightName+"_grads").c_str());

   Gradients *bgrad = new Gradients(g, optimizer, layer->getBiases(), (biasName+"_grads").c_str());

   gradients.push_back(wgrad);
   gradients.push_back(bgrad);

   ApplyGradientDescent *wgd = new ApplyGradientDescent(g, layer->getWeights(), lrconst, wgrad, (weightName+"_apply_grad").c_str());

   ApplyGradientDescent *bgd = new ApplyGradientDescent(g, layer->getBiases(), lrconst, bgrad, (biasName+"_apply_grad").c_str());

   gradientAppliers.push_back(wgd);
   gradientAppliers.push_back(bgd);
}

void SGDOptimizer::optimize(TfSession *session, std::list<TfOperation*> inputOps, std::list<Tensor*> inputTensors)
{
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptyTensors;

   session->run(inputOps, inputTensors, empty, emptyTensors, gradientAppliers);
}

