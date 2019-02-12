#ifndef _ASSIGN_OP_H_
#define _ASSIGN_OP_H_

#include "tfoperation.h"
#include <string>
#include <tensorflow/c/c_api.h>

class TfGraph;
class AssignOp : public TfOperation
{
   public:
      AssignOp(TfGraph *g, TfOperation *val, TfOperation *var, const char* name);
      ~AssignOp();
};

#endif // _ASSIGN_OP_H_
