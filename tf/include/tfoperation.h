#ifndef _TF_OPERATION_H_
#define _TF_OPERATION_H_

struct TF_Operation;
struct TF_Graph;
class TfOperation
{
   public:
      TfOperation(TF_Graph *g);
      ~TfOperation();

      TF_Operation *getOp(){ return op; };
   protected:
      TF_Operation *op;
      TF_Graph *graph;
};

#endif // _TF_OPERATION_H_
