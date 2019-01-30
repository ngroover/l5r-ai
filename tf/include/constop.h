#ifndef _CONST_OP_H_
#define _CONST_OP_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class Tensor;
class ConstOp : public TfOperation
{
   public:
      ConstOp(TfGraph *g, Tensor *t, const char* name);
      ~ConstOp();
};

#endif // _CONST_OP_H_
