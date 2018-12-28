#ifndef _CONFLICT_MANAGER_H_
#define _CONFLICT_MANAGER_H_

#include "gamestate.h"
#include "carddatamanager.h"
#include "choice.h"

namespace l5r
{
   class conflictManager
   {
      public:
         conflictManager( conflictState *globalState,
               std::shared_ptr<cardDataManager> cardMgr);
         ~conflictManager();

         // setup pointers
         void setGlobalState(conflictState *globalState);
         void setAttacker(conflictPlayerState *attacker, std::string attackerName);
         void setDefender(conflictPlayerState *defender, std::string defenderName);

         // modifiers
         void addAttackingCharacter(int cardIndex);
         void addDefendingCharacter(int cardIndex);
         void chooseContestedProvince(int cardIndex);
         void chooseContestedRing(ring r);
         void chooseConflictType(conflicttype ct);
         void passConflict();
         void unclaimAllRings();
         void initializeConflicts();
         void chooseConflictRing(ring r);

         // get choices
         std::list<choice> getConflictChoices();
         std::list<choice> getConflictRingChoices();
         std::string getRingName(ring r);

         // state information
         bool attackerWonConflict();
         bool defenderWonConflict();
         bool provinceBroke();
         bool wasUnopposed();
         bool wasDraw();

         // string names
         std::list<std::string> getAttackerNames();
         std::list<std::string> getDefenderNames();
         std::string getContestedProvinceName();
         std::string getConflictRingName();
         std::string getConflictTypeName(conflicttype type);
         std::string getCurrentConflictTypeName();

      private:
         std::shared_ptr<cardDataManager> cardMgr;

         conflictState *global;
         conflictPlayerState *attacker,*defender;
         std::string attackerName,defenderName;
   };
}

#endif //_CONFLICT_MANAGER_H_
