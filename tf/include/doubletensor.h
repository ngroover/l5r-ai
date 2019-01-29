#ifndef _DOUBLE_TENSOR_H_
#define _DOUBLE_TENSOR_H_

#include <tensorflow/c/c_api.h>

struct TF_Tensor;
class DoubleTensor
{
   public:
      DoubleTensor(const int64_t *dims,
         const int64_t num_dims,
         const double* data);
      DoubleTensor(const int64_t *dims, const int64_t num_dims);
      DoubleTensor();
      ~DoubleTensor();

      void print();
   protected:
      friend class ConstOp;
      friend class TfSession;
      TF_Tensor *tensor;
};

#endif // _DOUBLE_TENSOR_H_
