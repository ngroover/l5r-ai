#ifndef _VARIABLE_READ_H_
#define _VARIABLE_READ_H_

#include "tfoperation.h"
#include <string>
#include <tensorflow/c/c_api.h>

class TfGraph;
class Tensor;
class Variable;
class VariableRead : public TfOperation
{
   public:
      VariableRead(TfGraph *g, Variable *v, const char* name);
      ~VariableRead();
};

#endif // _VARIABLE_READ_H_
