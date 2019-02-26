#ifndef _GAME_SESSION_H_
#define _GAME_SESSION_H_

#include "tfsession.h"

namespace l5r
{
   class GameGraph;
   class GameSession
   {
      public:
         GameSession(GameGraph *graph);
         ~GameSession();

         TfSession *getSession();

      private:
         GameGraph *graph;
         TfSession session;
   };
};
#endif // _GAME_SESSION_H_
