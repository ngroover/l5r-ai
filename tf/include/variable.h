#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include "tfoperation.h"
#include <string>
#include <tensorflow/c/c_api.h>

class TfGraph;
class Tensor;
class Variable : public TfOperation
{
   public:
      Variable(TfGraph *g, TF_DataType dtype, const int64_t *dims, int dims_size, const char* name);
      ~Variable();
};

#endif // _VARIABLE_H_
