#ifndef _RESTORE_OP_H_
#define _RESTORE_OP_H_

#include "tfoperation.h"
#include <list>
#include <tensorflow/c/c_api.h>

class TfGraph;
class RestoreOp : public TfOperation
{
   public:
      RestoreOp(TfGraph *g, TfOperation *prefix, TfOperation *tensorName, TfOperation *shapes, std::list<TF_DataType> tensors, const char* name);
      ~RestoreOp();
};

#endif // _RESTORE_OP_H_
