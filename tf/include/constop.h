#ifndef _CONST_OP_H_
#define _CONST_OP_H_

#include "tfoperation.h"
#include <string>

class TfGraph;
class DoubleTensor;
class ConstOp : public TfOperation
{
   public:
      ConstOp(TfGraph *g, DoubleTensor *t, std::string name);
      ~ConstOp();
};

#endif // _CONST_OP_H_
