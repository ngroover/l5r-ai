#ifndef _SIGMOID_H_
#define _SIGMOID_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class Sigmoid : public TfOperation
{
   public:
      Sigmoid(TfGraph *g, TfOperation *x, const char* name);
      ~Sigmoid();
};

#endif // _SIGMOID_H_
