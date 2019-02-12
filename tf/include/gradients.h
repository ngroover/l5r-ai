#ifndef _GRADIENTS_H_
#define _GRADIENTS_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class Gradients : public TfOperation
{
   public:
      Gradients(TfGraph *g, TfOperation *x, TfOperation *out, const char* name);
      ~Gradients();
};

#endif // _GRADIENTS_H_
