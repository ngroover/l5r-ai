#ifndef _BIAS_ADD_H_
#define _BIAS_ADD_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class BiasAdd : public TfOperation
{
   public:
      BiasAdd(TfGraph *g, TfOperation *x, TfOperation *y, const char* name);
      ~BiasAdd();
};

#endif // _BIAS_ADD_H_
