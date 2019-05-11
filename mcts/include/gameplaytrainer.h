#ifndef _GAMEPLAY_TRAINER_H_
#define _GAMEPLAY_TRAINER_H_

#include <memory>
#include <list>

namespace l5r
{
   class GameGraph;
   class GameSession;
   class MctsStateNode;
   class GamestateEncoder;
   class PolicyEncoder;
   typedef std::shared_ptr<MctsStateNode> MctsStateNodePtr;
   class GameplayTrainer
   {
      public:
         GameplayTrainer(std::list<MctsStateNodePtr> states, GameGraph *graph, GameSession *session, GamestateEncoder *encoder,
            PolicyEncoder *polEncoder);
         ~GameplayTrainer();

         void train(int iterations);

      private:
         std::list<MctsStateNodePtr> statelist;
         GameGraph *graph;
         GameSession *session;
         GamestateEncoder *encoder;
         PolicyEncoder *polEncoder;
   };
};
#endif // _GAMEPLAY_TRAINER_H_
