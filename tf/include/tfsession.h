#ifndef _TF_SESSION_H_
#define _TF_SESSION_H_

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
         TfOperation *outputop, Tensor *output);
   private:
      TF_Session *session;
};

#endif // _TF_SESSION_H_
