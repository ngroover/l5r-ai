#include "layerinitializer.h"
#include "denselayer.h"
#include "tfsession.h"
#include "tfgraph.h"
#include "tfoperation.h"
#include "assignop.h"
#include "restoreop.h"
#include "saveop.h"
#include "stringtensor.h"
#include "constop.h"
#include <tensorflow/c/c_api.h>

LayerInitializer::LayerInitializer()
{
   restore = NULL;
   saveOp = NULL;

   prefixConst = NULL;
   tensorNamesConst = NULL;
   shapesConst = NULL;
}

LayerInitializer::~LayerInitializer()
{
   if(restore != NULL)
   {
      for( auto op : restoreList )
      {
         delete op;
      }
   }
   if(saveOp != NULL)
   {
      delete saveOp;
   }
   if(prefixConst != NULL)
   {
      delete prefixConst;
   }
   if(tensorNamesConst != NULL)
   {
      delete tensorNamesConst;
   }
   if(shapesConst != NULL)
   {
      delete shapesConst;
   }
}

void LayerInitializer::addLayer(DenseLayer *layer)
{
   layerList.push_back(layer);
}

void LayerInitializer::load(TfGraph *g, TfSession *session, std::string name)
{
   // NOTE: name is set the first time load is called because
   // it's const.  could use placeholder here instead and
   // generate the graph pieces once
   if(restore == NULL)
   {
      if(prefixConst == NULL)
      {
         // create common ops
         createCommonOps(g, session, name);
      }

      std::list<TF_DataType> typeList;
      for(auto layer : layerList)
      {
         // TODO: actually read types instead of hardcode doubles
         typeList.push_back(TF_DOUBLE);
         typeList.push_back(TF_DOUBLE);
      }

      // create restore operation
      restore = new RestoreOp(g, prefixConst, tensorNamesConst, shapesConst, typeList, "restoreOp");

      restoreList.push_back(restore);
      // create assignment ops
      int index=0;
      for(auto layer : layerList )
      {
         // weight assignment
         std::string opname = "restoreweight"+std::to_string(index);
         AssignOp *assignment = new AssignOp(g, restore, layer->getWeights(), index, opname.c_str());
         restoreList.push_back(assignment);

         // bias assignment
         opname = "restorebias"+std::to_string(index);
         assignment = new AssignOp(g, restore, layer->getBiases(), index+1, opname.c_str());
         restoreList.push_back(assignment);

         index += 2;
      }
   }
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptytensor;
   session->run(empty, emptytensor, empty, emptytensor, restoreList);
}

void LayerInitializer::createCommonOps(TfGraph *g, TfSession *session, std::string name)
{
   // prefix
   std::list<std::string> prefix = {name};
   const int64_t dims[] = {1};
   StringTensor prefixTensor(NULL, 0, prefix);
   prefixConst = new ConstOp(g, &prefixTensor, "prefixConst");

   // tensor names, shapes and types
   std::list<std::string> tensorList;
   std::list<std::string> shapesList;
   for(auto layer : layerList )
   {
      tensorList.push_back(layer->getWeightsName());
      tensorList.push_back(layer->getBiasesName());
      shapesList.push_back("");
      shapesList.push_back("");
   }
   const int64_t tensorDims = tensorList.size();
   StringTensor tensorNamesTensor(&tensorDims, 1, tensorList);
   tensorNamesConst = new ConstOp(g, &tensorNamesTensor, "tensorNamesConst");

   // shapes and slices
   StringTensor shapesTensor(&tensorDims, 1, shapesList);
   shapesConst = new ConstOp(g, &shapesTensor, "shapesConst");
}

void LayerInitializer::save(TfGraph *g, TfSession *session, std::string name)
{
   if(saveOp == NULL)
   {
      if(prefixConst == NULL)
      {
         // create common ops
         createCommonOps(g, session, name);
      }

      std::list<TfOperation*> tOps;
      for(auto layer : layerList)
      {
         tOps.push_back(layer->getWeights());
         tOps.push_back(layer->getBiases());
      }

      // create save operation
      saveOp = new SaveOp(g, prefixConst, tensorNamesConst, shapesConst, tOps, "saveOp");
   }
   std::list<TfOperation*> saveList= {saveOp};
   std::list<TfOperation*> empty;
   std::list<Tensor*> emptytensor;
   session->run(empty, emptytensor, empty, emptytensor, saveList);
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
