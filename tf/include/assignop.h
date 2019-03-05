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
      AssignOp(TfGraph *g, TfOperation *val, TfOperation *var, int index, const char* name);
      ~AssignOp();

   private:
      void initialize(TfGraph *g, TfOperation *val, TfOperation *var, int index, const char* name);
};

#endif // _ASSIGN_OP_H_
