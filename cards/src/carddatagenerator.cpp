#include "carddatagenerator.h"
#include <glog/logging.h>
#include <dirent.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <iostream>

using namespace l5r;

CardDataGenerator::CardDataGenerator(std::string pathToCardData)
{
   LOG(INFO) << "Loading json card data from " << pathToCardData;

   std::string data("{ \"cards\": [");  // one big data string
   DIR *dir;
   struct dirent *ent;
   bool is_first=true; // prepend a comma on every row except the first
   if ((dir = opendir (pathToCardData.c_str())) != NULL)
   {
      while ((ent = readdir (dir)) != NULL)
      {
         std::ifstream ifile;
         std::string fname(ent->d_name);
         if( fname != "." && fname != ".." )
         {
            ifile.open(pathToCardData+"/"+fname);
            if(ifile.is_open())
            {
               std::stringstream ss;
               ss << ifile.rdbuf();
               if(is_first)
               {
                  is_first = false;
               }
               else
               {
                  data += ", ";
               }
               data += ss.str();
            }
            else
            {
               LOG(ERROR) << "Failed to load " << fname << std::endl;;
            }
         }
      }
      closedir (dir);
      data += " ] } ";

      nlohmann::json cardData = nlohmann::json::parse(data);

      // loop through the json data and create map
      for ( auto &cd : cardData["cards"] )
      {
         try
         {
            std::string name = cd[0]["name"];
            std::string id = cd[0]["id"];

            // convert cardtype
            cardtype ct = cardtype::invalid;
            if(cd[0]["type"] == "stronghold")
            {
               ct = cardtype::stronghold;
            }
            else if(cd[0]["type"] == "role")
            {
               ct = cardtype::role;
            }
            else if(cd[0]["type"] == "province")
            {
               ct = cardtype::province;
            }
            else if(cd[0]["type"] == "character")
            {
               ct = cardtype::character;
            }
            else if(cd[0]["type"] == "holding")
            {
               ct = cardtype::holding;
            }
            else if(cd[0]["type"] == "event")
            {
               ct = cardtype::event;
            }
            else if(cd[0]["type"] == "attachment")
            {
               ct = cardtype::attachment;
            }

            // determine deckside
            deckside ds = deckside::none;
            if(cd[0]["side"] == "dynasty")
            {
               ds = deckside::dynasty;
            }
            else if(cd[0]["side"] == "conflict")
            {
               ds = deckside::conflict;
            }
            else if(cd[0]["side"] == "role")
            {
               ds = deckside::role;
            }
            else if(cd[0]["side"] == "province")
            {
               ds = deckside::province;
            }

            // TODO: actually detect this
            bool canBeStronghold = true;
            int provinceStr = 0;
            if(!cd[0]["strength"].is_null())
            {
               std::string str = cd[0]["strength"].get<std::string>();
               if(str[0] != 'X') // web of lies currently has a variable province strength of X, avoid this for now
               {
                  provinceStr = std::stoi(str);
               }
            }

            int strongholdHonor = 0;
            if(!cd[0]["honor"].is_null())
            {
               strongholdHonor = cd[0]["honor"];
            }

            int fateCost = 0;
            if(!cd[0]["cost"].is_null())
            {
               fateCost = cd[0]["cost"];
            }

            int strongholdFate = 0;
            if(!cd[0]["fate"].is_null())
            {
               fateCost = cd[0]["fate"];
            }

            int militarySkill = 0;
            bool militaryDash = false;
            if(!cd[0]["military"].is_null())
            {
               militarySkill = std::stoi(cd[0]["military"].get<std::string>());
            }
            else
            {
               militaryDash = true;
            }

            int politicalSkill = 0;
            bool politicalDash = false;
            if(!cd[0]["political"].is_null())
            {
               politicalSkill = std::stoi(cd[0]["political"].get<std::string>());
            }
            else
            {
               politicalDash = true;
            }

            int glory = 0;
            if(!cd[0]["glory"].is_null())
            {
               glory = cd[0]["glory"];
            }

            int holdingBonus = 0;
            if(!cd[0]["strength_bonus"].is_null())
            {
               std::string bonus = cd[0]["strength_bonus"];
               if(bonus[0] == '+')
               {
                  // substring off the + sign in the string if it's there
                  bonus = bonus.substr(1);
               }
               holdingBonus = std::stoi(bonus);
            }

            // generate actual carddata
            cardMap[id] = std::make_shared<CardData>(name, id, ct, canBeStronghold, provinceStr, strongholdHonor, fateCost, strongholdFate, ds, militarySkill, politicalSkill, glory, militaryDash, politicalDash, holdingBonus);
         }
         catch(const std::exception &e)
         {
            LOG(ERROR) << "Failed to parse json " << cd[0]["id"] << "(" << e.what() << ")";
         }
      }
   }
   else
   {
      LOG(FATAL) << "Could not open " << pathToCardData;
   }

   LOG(INFO) << "Done Loading json card data";
}

CardDataGenerator::~CardDataGenerator()
{
}

CardDataSharedPtr CardDataGenerator::generateCard(std::string targetCard)
{
   if(cardMap.find(targetCard) == cardMap.end())
   {
      LOG(ERROR) << "Could not find " << targetCard << std::endl;
   }
   return cardMap[targetCard];
}

