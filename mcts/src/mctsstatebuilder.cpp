#include "mctsstatebuilder.h"

using namespace l5r;

MctsStateBuilder::MctsStateBuilder(GamestateBuilder *builder, GameGraph *graph)
{
   this->builder = builder;
   this->graph = graph;
}

MctsStateBuilder::~MctsStateBuilder()
{
}

void MctsStateBuilder::buildState(gamestate &state)
{
}
