#include "mctsactionbuilder.h"
#include "policyencoder.h"
#include "mctsactionnode.h"
#include "mctsstatenode.h"
#include "engine.h"
#include <iostream>

using namespace l5r;

MctsActionBuilder::MctsActionBuilder(enginePtr eng, PolicyEncoder *encoder)
{
   this->eng = eng;
   this->encoder = encoder;
}

MctsActionBuilder::~MctsActionBuilder()
{
}

void MctsActionBuilder::buildActions(MctsStateNodePtr stateNode)
{
   if( !stateNode->isLeaf() && !stateNode->hasChildActions() )
   {
      eng->setGameState(stateNode->getState());
      decision d = eng->getDecision();

      std::list<choice> choiceList = d.getChoiceList();

      // create PolicyList
      PolicyList pl;
      for( auto cl : choiceList )
      {
         Policy p(cl);
         p.prob = 0.0;
         pl.push_back(p);
         //std::cout << "Available choice is " << cl.getText() << " " << cl.getNumber() << std::endl;
      }

      // decode the neural net output
      PolicyVector pv = stateNode->getPolicy();

      encoder->decode(pl, pv.data(), pv.size());

      for( auto p : pl )
      {
         //std::cout << "prob is " << p.prob << std::endl;
         MctsActionNodePtr a = std::make_shared<MctsActionNode>(p.c, p.prob, stateNode);
         stateNode->addChildAction(a);
      }
   }
}
