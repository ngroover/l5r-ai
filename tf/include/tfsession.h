#ifndef _TF_SESSION_H_
#define _TF_SESSION_H_

#include <list>

struct TF_Session;
class TfGraph;
class TfOperation;
class Tensor;
class TfSession
{
   public:
      TfSession(TfGraph *graph);
      ~TfSession();

      void run(TfOperation *inputop, Tensor *input,
         std::list<TfOperation*> outputs, std::list<Tensor*> outputTensors, std::list<TfOperation*> targetop);
   private:
      TF_Session *session;
};

#endif // _TF_SESSION_H_
