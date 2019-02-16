#include "tfsession.h"
#include "tfgraph.h"
#include "tensor.h"
#include "tfoperation.h"
#include <tensorflow/c/c_api.h>
#include <stdio.h>

TfSession::TfSession(TfGraph *graph)
{
   TF_SessionOptions *opts = TF_NewSessionOptions();
   TF_Status *status = TF_NewStatus();
   session = TF_NewSession(graph->getGraph(), opts, status);
   TF_DeleteStatus(status);
}

TfSession::~TfSession()
{
   TF_Status *status = TF_NewStatus();
   TF_CloseSession(session, status);
   TF_DeleteSession(session, status);
   TF_DeleteStatus(status);
}


void TfSession::run(TfOperation *inputop, Tensor *input,
         TfOperation *outputop, Tensor *output, std::list<TfOperation*> targetops)
{
   TF_Output tfout,tfin;
   TF_Output *out=NULL, *in=NULL;
   TF_Tensor **outtensor=NULL, **intensor=NULL;
   int inputNum=0, outputNum=0;
   TF_Operation *tfops[targetops.size()];
   TF_Operation **target=NULL;

   if( inputop != NULL )
   {
      tfin.oper=(TF_Operation*)inputop->getOp();
      tfin.index=0;
      in = &tfin;
      intensor = input->getTensor();
      inputNum=1;
   }
   if( outputop != NULL )
   {
      tfout.oper=(TF_Operation*)outputop->getOp();
      tfout.index=0;
      out = &tfout;
      outtensor = output->getTensor();
      outputNum=1;
   }

   TF_Status *status = TF_NewStatus();
   if( targetops.size() > 0 )
   {
      target = tfops;
      for(auto targetop : targetops)
      {
         *target = targetop->getOp();
         target++;
      }
      target = tfops;
   }

   TF_SessionRun(session,
      NULL, // options
      in, intensor, inputNum, // inputs
      out, outtensor, outputNum, // outputs
      target, targetops.size(), NULL, status);

   TF_DeleteStatus(status);
}
