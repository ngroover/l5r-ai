#ifndef _GAMESTATE_INTFC_H_
#define _GAMESTATE_INTFC_H_

#include <string>
#include <memory>

namespace l5r
{
   class gamestate;
   class tokenstate;
   class GameStateIntfc
   {
      public:
         GameStateIntfc(std::shared_ptr<gamestate> ptr, std::string player1Name, std::string player2Name);
         ~GameStateIntfc();

         tokenstate *getPlayerTokens();
         tokenstate *getOpponentTokens();

         std::string getPlayerName();
         std::string getOpponentName();

      private:
         std::shared_ptr<gamestate> state;
         std::string player1,player2;
   };
};

#endif // _GAMESTATE_INTFC_H_
