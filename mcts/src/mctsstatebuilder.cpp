#include "mctsstatebuilder.h"
#include "mctsstatenode.h"
#include "policyencoder.h"
#include "gamegraph.h"
#include "gamesession.h"
#include "gamestateencoder.h"
#include "gamesession.h"
#include <iostream>

using namespace l5r;

MctsStateBuilder::MctsStateBuilder(GamestateEncoder *encoder, PolicyEncoder *polEncoder, GameGraph *graph, GameSession *session)
{
   this->encoder = encoder;
   this->graph = graph;
   this->polEncoder = polEncoder;
   this->session = session;
   policyVector.resize(polEncoder->getTotalSize());
   gameVector.resize(encoder->getTotalSize());
}

MctsStateBuilder::~MctsStateBuilder()
{
}

MctsStateNodePtr MctsStateBuilder::buildState(gamestate state)
{
   // TODO: check already existing nodes

   // search entire list so we can reuse
   for(auto s : entireList)
   {
      if(state == s->getState())
      {
         std::cout << "Found state. Reusing it" << std::endl;
         // found it return
         return s;
      }
   }

   double value = 0.0;
   bool leaf = false;
   if( state.currentPhase == phase::gameover)
   {
      // game over condition
      if(state.winner == player::player1)
      {
         value = 1.0;
      }
      else
      {
         value = -1.0;
      }
      leaf = true;
   }
   else
   {
      encoder->encode(&state, gameVector.data(), gameVector.size());
      graph->compute(session, gameVector.data(), gameVector.size(), &value, policyVector.data(), policyVector.size());
   }

   MctsStateNodePtr newState = std::make_shared<MctsStateNode>(state, policyVector, value, leaf);

   entireList.push_back(newState);

   return newState;
}

std::list<MctsStateNodePtr> MctsStateBuilder::getStateList()
{
   return entireList;
}
