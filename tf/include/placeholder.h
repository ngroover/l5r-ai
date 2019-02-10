#ifndef _PLACEHOLDER_H_
#define _PLACEHOLDER_H_

#include "tfoperation.h"
#include <string>
#include <tensorflow/c/c_api.h>

class TfGraph;
class Tensor;
class Placeholder : public TfOperation
{
   public:
      Placeholder(TfGraph *g, TF_DataType dtype, const int64_t *dims, int dims_size, const char* name);
      ~Placeholder();
};

#endif // _PLACEHOLDER_H_
