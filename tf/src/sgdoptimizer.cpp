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
#include <string.h>

SGDOptimizer::SGDOptimizer(TfGraph *g, double learningRate, TfOperation *optimizer, const char *name)
{
   this->learningrate = learningRate;
   lrtensor = new DoubleTensor(NULL, 0, &this->learningrate);
   strcpy(optimizerName, name);

   char learningrate_name[64];
   strcpy(learningrate_name, name);
   strcat(learningrate_name, "_lr_rate");
   lrconst = new ConstOp(g, lrtensor, learningrate_name);
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
   std::string prefix = optimizerName;
   prefix += "_layer" + std::to_string(layerNum++);
   std::string weightName = prefix+"_weight";
   std::string biasName = prefix+"_bias";

   Gradients *wgrad = new Gradients(g, optimizer, layer->getWeights(), (weightName+"_grads").c_str());

   Gradients *bgrad = new Gradients(g, optimizer, layer->getBiases(), (biasName+"_grads").c_str());

   gradients.push_back(wgrad);
   // debug information
   weightgrads.push_back(layer->getWeights());
   weightgrads.push_back(wgrad);
   gradients.push_back(bgrad);

   ApplyGradientDescent *wgd = new ApplyGradientDescent(g, layer->getWeights(), lrconst, wgrad, (weightName+"_apply_grad").c_str());

   ApplyGradientDescent *bgd = new ApplyGradientDescent(g, layer->getBiases(), lrconst, bgrad, (biasName+"_apply_grad").c_str());

   gradientAppliers.push_back(wgd);
   gradientAppliers.push_back(bgd);
}

void SGDOptimizer::optimize(TfSession *session, std::list<TfOperation*> inputOps, std::list<Tensor*> inputTensors)
{
   DoubleTensor gradlist[weightgrads.size()];

   std::list<Tensor*> tensors;
   std::list<TfOperation*> empty;
   for(int i=0;i<weightgrads.size();i++)
   {
      tensors.push_back(&gradlist[i]);
   }

   session->run(inputOps, inputTensors, weightgrads, tensors, gradientAppliers);

   // print debug information
   for(int i=0;i<weightgrads.size();i++)
   {
      printf("size = %d ", gradlist[i].getSize());
      if( i % 3 == 0)
      {
         printf("weights %s %d\n", optimizerName, i);
      }
      else
      {
         printf("Grad %s %d\n", optimizerName, i);
      }
      gradlist[i].printStats();
   }
}

