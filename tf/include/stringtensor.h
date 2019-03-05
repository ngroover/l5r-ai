#ifndef _STRING_TENSOR_H_
#define _STRING_TENSOR_H_

#include <tensorflow/c/c_api.h>
#include <list>
#include <string>
#include "tensor.h"

struct TF_Tensor;
class StringTensor : public Tensor
{
   public:
      StringTensor(const int64_t *dims,
         const int64_t num_dims,
         std::list<std::string> strList);
         // not sure you can allocate a string tensor without string sizes
//      StringTensor(const int64_t *dims, const int64_t num_dims);
      StringTensor();
      ~StringTensor();

      void print();
};

#endif // _STRING_TENSOR_H_
