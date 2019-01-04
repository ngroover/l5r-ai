#ifndef _TOKEN_MANAGER_H_
#define _TOKEN_MANAGER_H_

#include "state/gamestate.h"
#include "choice.h"
#include "carddatamanager.h"
#include <memory>
#include <list>

namespace l5r
{
   class tokenManager
   {
      public:
         tokenManager(std::shared_ptr<gamestate> state,
                        std::shared_ptr<cardDataManager> cardMgr);
         ~tokenManager();

         void setHonor(int honor, int playerNum, std::string playerName);
         void gainHonor(int honor, playerstate &pState, std::string playerName);
         void setHonorDial(int honor, playerstate &pState, std::string playerNae);
         int getHonorDial(playerstate &pState);
         void gainFate(int honor, playerstate &pState, std::string playerName);

         int getFate(playerstate &pState);

         void addFateToCard(playerstate &pState, int cardIndex, int extraFate);

         std::list<choice> getAdditionalFateChoices(playerstate &pState, int cardIndex);

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};
#endif // _TOKEN_MANAGER_H_
