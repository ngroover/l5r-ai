#ifndef _INT32_TENSOR_H_
#define _INT32_TENSOR_H_

#include <tensorflow/c/c_api.h>
#include "tensor.h"

struct TF_Tensor;
class Int32Tensor : public Tensor
{
   public:
      Int32Tensor(const int64_t *dims,
         const int64_t num_dims,
         const int32_t* data);
      Int32Tensor(const int64_t *dims, const int64_t num_dims);
      Int32Tensor();
      ~Int32Tensor();

      void print();
};

#endif // _INT32_TENSOR_H_
