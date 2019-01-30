#ifndef _MATMUL_OP_H_
#define _MATMUL_OP_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class MatMulOp : public TfOperation
{
   public:
      MatMulOp(TfGraph *g, TfOperation *x, TfOperation *y, const char* name);
      ~MatMulOp();
};

#endif // _MATMUL_OP_H_
