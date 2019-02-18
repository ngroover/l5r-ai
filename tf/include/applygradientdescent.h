#ifndef _APPLY_GRADIENT_DESCENT_H_
#define _APPLY_GRADIENT_DESCENT_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class ApplyGradientDescent : public TfOperation
{
   public:
      ApplyGradientDescent(TfGraph *g, TfOperation *var, TfOperation *lr, TfOperation *delta, const char* name);
      ~ApplyGradientDescent();
};

#endif // _APPLY_GRADIENT_DESCENT_H_
