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


void TfSession::run(std::list<TfOperation*> inputs, std::list<Tensor*> inputTensors,
         std::list<TfOperation*> outputs, std::list<Tensor*> outputTensors, std::list<TfOperation*> targetops)
{
   TF_Output tfout[outputs.size()];
   TF_Output tfin[inputs.size()];
   TF_Output *out=NULL, *in=NULL;
   TF_Tensor **outtensor=NULL, **intensor=NULL;
   TF_Tensor *outtensors[outputs.size()];
   TF_Tensor *intensors[inputs.size()];
   TF_Operation *tfops[targetops.size()];
   TF_Operation **target=NULL;

   // process inputs
   if( inputs.size() > 0 && inputs.size() == inputTensors.size())
   {
      in = tfin;
      intensor = intensors;
      auto inTensorIter = inputTensors.begin();
      for(auto input : inputs)
      {
         in->oper =(TF_Operation*)input->getOp();
         in->index=0;
         *intensor = *((*inTensorIter)->getTensor());
         inTensorIter++;
         in++;
         intensor++;
      }
      in = tfin;
      intensor = intensors;
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

   // process target ops
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

   TF_Status *status = TF_NewStatus();

   TF_SessionRun(session,
      NULL, // options
      in, intensor, inputs.size(), // inputs
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
