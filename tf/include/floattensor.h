#ifndef _FLOAT_TENSOR_H_
#define _FLOAT_TENSOR_H_

#include "tensor.h"
#include <tensorflow/c/c_api.h>

struct TF_Tensor;
class FloatTensor : public Tensor
{
   public:
      FloatTensor(const int64_t *dims,
         const int64_t num_dims,
         const float* data);
      FloatTensor(const int64_t *dims, const int64_t num_dims);
      FloatTensor();
      ~FloatTensor();

      void print();
};

#endif // _FLOAT_TENSOR_H_
