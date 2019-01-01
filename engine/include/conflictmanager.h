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
         void addAttackingCharacter(inplaycharacter character);
         void addDefendingCharacter(inplaycharacter character);

         void bowAttackers();
         void bowDefenders();

         std::list<inplaycharacter> removeAllAttackingCharacters();
         std::list<inplaycharacter> removeAllDefendingCharacters();

         void chooseContestedProvince(int cardIndex);
         void chooseContestedRing(ring r);
         void chooseConflictType(conflicttype ct);
         void passConflict();
         void completeConflict();
         bool attackerHasConflictsLeft();
         bool defenderHasConflictsLeft();
         void attackerClaimRing();
         void defenderClaimRing();
         void contestedRingUnclaimed();

         void initializeRings();
         void unclaimRings();
         void putFateOnRings();
         void initializeFavor();
         bool attackerGainsFavor(int attackerGlory, int defenderGlory);
         bool defenderGainsFavor(int attackerGlory, int defenderGlory);
         void changeFavorType(conflicttype newtype);

         void initializeConflicts();
         void chooseConflictRing(ring r);

         // get choices
         std::list<choice> getConflictChoices();
         std::list<choice> getConflictRingChoices();
         std::string getRingName(ring r);
         std::list<choice> getFavorChoices();

         // state information
         bool attackerWonConflict();
         bool defenderWonConflict();
         bool provinceBroke();
         bool wasUnopposed();
         int getContestedProvince();

         // string names
         std::list<std::string> getAttackerNames();
         std::list<std::string> getDefenderNames();
         std::string getContestedProvinceName();
         std::string getConflictRingName();
         std::string getConflictTypeName(conflicttype type);
         std::string getCurrentConflictTypeName();

         // print functions
         void printConflictResult();

      private:
         int calculateStr(conflictPlayerState *player);
         std::shared_ptr<cardDataManager> cardMgr;

         conflictState *global;
         conflictPlayerState *attacker,*defender;
         std::string attackerName,defenderName;
   };
}

#endif //_CONFLICT_MANAGER_H_
