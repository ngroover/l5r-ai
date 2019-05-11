#include "gameplaytrainer.h"
#include "mctsstatenode.h"
#include "mctsactionnode.h"
#include "policyencoder.h"
#include "gamestateencoder.h"
#include <iostream>

using namespace l5r;

GameplayTrainer::GameplayTrainer(std::list<MctsStateNodePtr> states, GameGraph *graph, GameSession *session, GamestateEncoder *encoder,
   PolicyEncoder *polEncoder)
{
   statelist = states;
   this->graph = graph;
   this->session = session;
   this->encoder = encoder;
   this->polEncoder = polEncoder;
}

GameplayTrainer::~GameplayTrainer()
{
}

void GameplayTrainer::train(int iterations)
{
   for(auto sl : statelist)
   {
      if(sl->getValue() > 0.8 || sl->getValue() < -0.8)
      {
         std::cout << "-----State------" << std::endl;
         std::cout << "visits=" << sl->getVisits() << std::endl;
         std::cout << "player1turn=" << (sl->player1Turn() ? "true" : "false") << std::endl;
         std::cout << "value=" << sl->getValue() << std::endl;
         for(auto act: sl->getChildActions())
         {
            std::cout << "---------Actions--------" << std::endl;
            std::cout << "name=" << act->getChoice().getText() << std::endl;
            std::cout << "visits=" << act->getVisits() << std::endl;
            std::cout << "reward=" << act->getReward() << std::endl;
         }
         std::cout << "Press a key" << std::endl;
         std::cin.get();
      }
   }
}
