#include "gamestatebuilder.h"
#include <iostream>

using namespace l5r;

GamestateBuilder::GamestateBuilder(int numCharacter, int numHoldings,
            int numProvinces)
{
   this->numCharacter = numCharacter;
   this->numHoldings = numHoldings;
   this->numProvinces = numProvinces;
   numRings = 5;   // should always be 5 rings
   numPlayers = 2; // should always be 2 players

   int characterSize = (sizeof(CharacterSlot)/sizeof(double) * numCharacter);
   int holdingSize = (sizeof(HoldingSlot)/sizeof(double) * numHoldings);
   int provinceSize = (sizeof(ProvinceSlot)/sizeof(double) * numProvinces);
   int ringSize = (sizeof(RingSlot)/sizeof(double) * numRings);
   int playerSize = (sizeof(PlayerSlot)/sizeof(double) * numPlayers);
   int globalSize = (sizeof(GlobalSlot)/sizeof(double));

   totalSize = characterSize + holdingSize + provinceSize + ringSize + playerSize + globalSize;

   rawData = new double[totalSize];

   characters = (CharacterSlot*)&rawData[0];

   holdings = (HoldingSlot*)&rawData[characterSize];
   
   provinces = (ProvinceSlot*)&rawData[characterSize+holdingSize];

   rings = (RingSlot*)&rawData[characterSize+holdingSize+provinceSize];

   players = (PlayerSlot*)&rawData[characterSize+holdingSize+provinceSize+ringSize];

   global = (GlobalSlot*)&rawData[characterSize+holdingSize+provinceSize+ringSize+playerSize];
}

GamestateBuilder::~GamestateBuilder()
{
   delete[] rawData;
}

const int GamestateBuilder::getTotalSize()
{
   return totalSize;
}

CharacterSlot *GamestateBuilder::getCharacter(int index)
{
   if(index < numCharacter)
   {
      return characters+index;
   }
   else
   {
      std::cout << "Character index invalid" << std::endl;
   }
   return NULL;
}

HoldingSlot *GamestateBuilder::getHolding(int index)
{
   if(index < numHoldings)
   {
      return holdings+index;
   }
   else
   {
      std::cout << "Holding index invalid" << std::endl;
   }
   return NULL;
}

ProvinceSlot *GamestateBuilder::getProvince(int index)
{
   if(index < numProvinces)
   {
      return provinces+index;
   }
   else
   {
      std::cout << "Provinces index invalid" << std::endl;
   }
   return NULL;
}

RingSlot *GamestateBuilder::getRing(int index)
{
   if(index < numRings)
   {
      return rings+index;
   }
   else
   {
      std::cout << "Ring index invalid" << std::endl;
   }
   return NULL;
}

PlayerSlot *GamestateBuilder::getPlayer(int index)
{
   if(index < numPlayers)
   {
      return players+index;
   }
   else
   {
      std::cout << "Player index invalid" << std::endl;
   }
   return NULL;
}

GlobalSlot *GamestateBuilder::getGlobal()
{
   return global;
}

double *GamestateBuilder::getRawData()
{
   return rawData;
}
