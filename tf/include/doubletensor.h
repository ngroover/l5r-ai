#ifndef _DOUBLE_TENSOR_H_
#define _DOUBLE_TENSOR_H_

#include <tensorflow/c/c_api.h>
#include "tensor.h"

struct TF_Tensor;
class DoubleTensor : public Tensor
{
   public:
      DoubleTensor(const int64_t *dims,
         const int64_t num_dims,
         const double* data);
      DoubleTensor(const int64_t *dims, const int64_t num_dims);
      DoubleTensor();
      ~DoubleTensor();

      void print();
};

#endif // _DOUBLE_TENSOR_H_
