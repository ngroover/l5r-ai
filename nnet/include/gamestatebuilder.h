#ifndef _GAMESTATE_BUILDER_H_
#define _GAMESTATE_BUILDER_H_

#include "characterslot.h"
#include "ringslot.h"
#include "holdingslot.h"
#include "provinceslot.h"
#include "playerslot.h"
#include "globalslot.h"

namespace l5r
{
   class GamestateBuilder
   {
      public:
         GamestateBuilder(int numCharacter, int numHoldings,
            int numProvinces);
         ~GamestateBuilder();

         const int getTotalSize();

         double *getRawData();

         CharacterSlot *getCharacter(int index);

         HoldingSlot *getHolding(int index);

         ProvinceSlot *getProvince(int index);

         // 5 rings
         RingSlot *getRing(int index);

         // 2 players
         PlayerSlot *getPlayer(int index);

         // 1 global
         GlobalSlot *getGlobal();
      private:
         double *rawData;
         int totalSize;

         CharacterSlot *characters;
         HoldingSlot *holdings;
         ProvinceSlot *provinces;
         RingSlot *rings;
         PlayerSlot *players;
         GlobalSlot *global;

         int numCharacter;
         int numHoldings;
         int numProvinces;
         int numRings;
         int numPlayers;
   };
};

#endif // _GAMESTATE_BUILDER_H_
