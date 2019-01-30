#ifndef _TENSOR_H_
#define _TENSOR_H_

#include <tensorflow/c/c_api.h>

struct TF_Tensor;
class Tensor
{
   public:
      Tensor();
      ~Tensor();

      TF_Tensor **getTensor(){ return &tensor; };
   protected:
      TF_Tensor *tensor;
};

#endif // _TENSOR_H_
