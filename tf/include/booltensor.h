#ifndef _BOOL_TENSOR_H_
#define _BOOL_TENSOR_H_

#include <tensorflow/c/c_api.h>
#include "tensor.h"

struct TF_Tensor;
class BoolTensor : public Tensor
{
   public:
      BoolTensor(const int64_t *dims,
         const int64_t num_dims,
         const bool* data);
      BoolTensor(const int64_t *dims, const int64_t num_dims);
      BoolTensor();
      ~BoolTensor();

      void print();
};

#endif // _BOOL_TENSOR_H_
