#ifndef _CHARACTER_MANIPULATOR_H_
#define _CHARACTER_MANIPULATOR_H_

#include <memory>
#include "card.h"

namespace l5r
{
   class GameStateIntfc;
   class cardDataManager;
   class cardarea;
   class conflictPlayerState;
   class CharacterManipulator
   {
      public:
         CharacterManipulator(std::shared_ptr<GameStateIntfc> stateIntfc,
            std::shared_ptr<cardDataManager> cardMgr);
         ~CharacterManipulator();
         
         void bowParticipants();
         void movePartipantsHome();

         void moveCharacterToConflict(conflictPlayerState *cps, cardarea *cards, CardSharedPtr cardChoice);

      private:
         std::shared_ptr<GameStateIntfc> stateIntfc;
         std::shared_ptr<cardDataManager> cardMgr;
   };
};
#endif // _CHARACTER_MANIPULATOR_H_
