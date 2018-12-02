#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <gamestate.h>
#include <action.h>
#include <list>
#include <agent.h>
#include <map>
#include <memory>
#include "agent.h"
#include "cardgenerator.h"
#include "engineshared.h"
#include "pregameengine.h"
#include "dynastyengine.h"


namespace l5r
{
   class engine
   {
      public:
         engine(std::unique_ptr<agent> player1, std::unique_ptr<agent> player2);
         ~engine();

         // useful for testing
         void setGameState(gamestate gs);

         gamestate getGameState();

         decision getDecision();

         void doAction(choice c);

         void run();
      private:
         std::shared_ptr<engineShared> shared;
         std::unique_ptr<pregameEngine> pregame;
         std::unique_ptr<dynastyEngine> dynasty;
         cardgenerator cg;

         //gamestate state;
         //std::unique_ptr<agent> player1,player2;
         
         //std::map<cards,card> cardList;

         std::map<cards,card> populateCards(std::unique_ptr<agent> &player, playercards &gameCards);
         // actiongenerator
         // actionprocessor
         // pregameinitializer
   };
};

#endif //_ENGINE_H_
