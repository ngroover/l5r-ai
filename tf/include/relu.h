#ifndef _RELU_H_
#define _RELU_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class Relu : public TfOperation
{
   public:
      Relu(TfGraph *g, TfOperation *x, const char* name);
      ~Relu();
};

#endif // _RELU_H_
