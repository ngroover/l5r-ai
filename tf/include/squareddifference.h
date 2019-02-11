#ifndef _SQUARED_DIFFERENCE_H_
#define _SQUARED_DIFFERENCE_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class SquaredDifference : public TfOperation
{
   public:
      SquaredDifference(TfGraph *g, TfOperation *x, TfOperation *y, const char* name);
      ~SquaredDifference();
};

#endif // _SQUARED_DIFFERENCE_H_
