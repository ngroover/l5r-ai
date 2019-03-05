#ifndef _SAVE_OP_H_
#define _SAVE_OP_H_

#include "tfoperation.h"
#include <list>
#include <string>

class TfGraph;
class DoubleTensor;
class SaveOp : public TfOperation
{
   public:
      SaveOp(TfGraph *g, TfOperation *prefix, TfOperation *tensorName, TfOperation *shapes, std::list<TfOperation *> tensors, const char* name);
      ~SaveOp();
};

#endif // _SAVE_OP_H_
