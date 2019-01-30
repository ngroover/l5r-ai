#ifndef _ADD_OP_H_
#define _ADD_OP_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class AddOp : public TfOperation
{
   public:
      AddOp(TfGraph *g, TfOperation *x, TfOperation *y, const char* name);
      ~AddOp();
};

#endif // _ADD_OP_H_
