#include "tfgraph.h"
#include <tensorflow/c/c_api.h>

TfGraph::TfGraph()
{
   graph = TF_NewGraph();
}

TfGraph::~TfGraph()
{
   TF_DeleteGraph(graph);
}
