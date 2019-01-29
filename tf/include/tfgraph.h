#ifndef _TF_GRAPH_H_
#define _TF_GRAPH_H_

struct TF_Graph;
class TfSession;
class TfGraph
{
   public:
      TfGraph();
      ~TfGraph();

      TF_Graph* getGraph(){return graph;};

   protected:
      TF_Graph *graph;
};

#endif // _TF_GRAPH_H_
