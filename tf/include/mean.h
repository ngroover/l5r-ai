#ifndef _MEAN_H_
#define _MEAN_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class Mean : public TfOperation
{
   public:
      Mean(TfGraph *g, TfOperation *x, TfOperation *y, const char* name);
      ~Mean();
};

#endif // _MEAN_H_
