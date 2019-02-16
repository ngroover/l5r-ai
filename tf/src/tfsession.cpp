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
         std::list<TfOperation*> outputs, std::list<Tensor*> outputTensors, std::list<TfOperation*> targetops)
{
   TF_Output tfout[outputs.size()];
   TF_Output tfin;
   TF_Output *out=NULL, *in=NULL;
   TF_Tensor **outtensor=NULL, **intensor=NULL;
   TF_Tensor *outtensors[outputs.size()];
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

   // process outputs
   if( outputs.size() > 0 && outputs.size() == outputTensors.size())
   {
      out = tfout;
      outtensor = outtensors;
      auto outTensorIter = outputTensors.begin();
      for(auto output : outputs)
      {
         out->oper =(TF_Operation*)output->getOp();
         out->index=0;
         *outtensor = *((*outTensorIter)->getTensor());
         outTensorIter++;
         out++;
         outtensor++;
      }
      out = tfout;
      outtensor = outtensors;
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
      out, outtensor, outputs.size(), // outputs
      target, targetops.size(), NULL, status);

   printf("%s\n", TF_Message(status));

   // copy tensor pointers back
   if( outputTensors.size() == outputs.size() )
   {
      outtensor = outtensors;
      for(auto outputTensor : outputTensors)
      {
         outputTensor->setTensor(*outtensor);
         outtensor++;
      }
   }

   TF_DeleteStatus(status);
}
