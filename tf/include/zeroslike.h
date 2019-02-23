#ifndef _ZEROS_LIKE_H_
#define _ZEROS_LIKE_H_

#include "tfoperation.h"
#include <tensorflow/c/c_api.h>
#include <string>

class TfGraph;
class DoubleTensor;
class ZerosLike : public TfOperation
{
   public:
      ZerosLike(TfGraph *g, TfOperation *x, TF_DataType dtype, const char* name);
      ~ZerosLike();
};

#endif // _ZEROS_LIKE_H_
