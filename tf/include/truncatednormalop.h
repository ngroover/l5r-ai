#ifndef _TRUNCATED_NORMAL_OP_H_
#define _TRUNCATED_NORMAL_OP_H_

#include "tfoperation.h"
#include <tensorflow/c/c_api.h>
#include <string>

class TfGraph;
class DoubleTensor;
class TruncatedNormalOp : public TfOperation
{
   public:
      TruncatedNormalOp(TfGraph *g, TfOperation *x, TF_DataType dtype, const char* name);
      ~TruncatedNormalOp();
};

#endif // _TRUNCATED_NORMAL_OP_H_
