#ifndef _PARAMETERIZED_TRUNCATED_NORMAL_H_
#define _PARAMETERIZED_TRUNCATED_NORMAL_H_

#include "tfoperation.h"
#include <tensorflow/c/c_api.h>
#include <string>

class TfGraph;
class DoubleTensor;
class ParameterizedTruncatedNormal : public TfOperation
{
   public:
      ParameterizedTruncatedNormal(TfGraph *g, TfOperation *inp, TfOperation *mean, TfOperation *stdev, TfOperation *minval, TfOperation *maxval, TF_DataType dtype, const char* name);
      ~ParameterizedTruncatedNormal();
};

#endif // _PARAMETERIZED_TRUNCATED_NORMAL_H_
