#ifndef _GAMESTATE_INTFC_H_
#define _GAMESTATE_INTFC_H_

#include <string>
#include <memory>

namespace l5r
{
   class gamestate;
   class tokenstate;
   class cardarea;
   class conflictPlayerState;
   class conflictState;
   class GameStateIntfc
   {
      public:
         GameStateIntfc(std::shared_ptr<gamestate> ptr, std::string player1Name, std::string player2Name);
         ~GameStateIntfc();

         std::shared_ptr<gamestate> getState();

         tokenstate *getPlayerTokens();
         tokenstate *getOpponentTokens();

         cardarea *getPlayerCards();
         cardarea *getOpponentCards();

         cardarea *getAttackerCards();
         cardarea *getDefenderCards();

         std::string getPlayerName();
         std::string getOpponentName();

         std::string getAttackerName();
         std::string getDefenderName();

         conflictPlayerState *getAttackerConflictState();
         conflictPlayerState *getDefenderConflictState();

         conflictState *getGlobalConflictState();

      private:
         std::shared_ptr<gamestate> state;
         std::string player1,player2;
   };
};

#endif // _GAMESTATE_INTFC_H_
