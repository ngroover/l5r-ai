#include "tfsession.h"
#include "tfgraph.h"
#include "doubletensor.h"
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


void TfSession::run(TfOperation *inputop, DoubleTensor *input,
         TfOperation *outputop, DoubleTensor *output)
{
   TF_Output tfout,tfin;
   TF_Output *out=NULL, *in=NULL;
   TF_Tensor **outtensor=NULL, **intensor=NULL;
   int inputNum=0, outputNum=0;
   if( inputop != NULL )
   {
      tfin.oper=(TF_Operation*)inputop->getOp();
      tfin.index=0;
      in = &tfin;
      intensor = &input->tensor;
      inputNum=1;
   }
   if( outputop != NULL )
   {
      tfout.oper=(TF_Operation*)outputop->getOp();
      tfout.index=0;
      out = &tfout;
      outtensor = &output->tensor;
      outputNum=1;
   }

   TF_Status *status = TF_NewStatus();

   TF_SessionRun(session,
      NULL, // options
      in, intensor, inputNum, // inputs
      out, outtensor, outputNum, // outputs
      NULL, 0, NULL, status);

   TF_DeleteStatus(status);
}
