#include "decklistmanager.h"
#include <glog/logging.h>
#include <dirent.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>

using namespace l5r;

DecklistManager::DecklistManager(std::string pathToDeckData)
{
   LOG(INFO) << "Loading json deck data from " << pathToDeckData;

   std::string data("{ \"decks\": [");  // one big data string
   DIR *dir;
   struct dirent *ent;
   bool is_first=true; // prepend a comma on every row except the first
   if ((dir = opendir (pathToDeckData.c_str())) != NULL)
   {
      while ((ent = readdir (dir)) != NULL)
      {
         std::ifstream ifile;
         std::string fname(ent->d_name);
         if( fname != "." && fname != ".." )
         {
            ifile.open(pathToDeckData+"/"+fname);
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

      nlohmann::json deckData = nlohmann::json::parse(data);

      // loop through the json data and create map
      for ( auto &cd : deckData["decks"] )
      {
         try
         {
            std::string name = cd["name"];
            std::vector<std::string> cardList;
            for( auto &c : cd["cards"])
            {
               cardList.push_back(c);
            }
            deckMap[name] = std::make_shared<Decklist>(name, cardList);
         }
         catch(const std::exception &e)
         {
            LOG(ERROR) << "Failed to parse json (" << e.what() << ")";
         }
      }
   }
   else
   {
      LOG(FATAL) << "Could not open " << pathToDeckData;
   }

   LOG(INFO) << "Done Loading json deck data";
}

DecklistManager::~DecklistManager()
{
}

DecklistSharedPtr DecklistManager::findDeck(std::string deckName)
{
   if(deckMap.find(deckName) == deckMap.end())
   {
      LOG(ERROR) << "Could not find " << deckName << std::endl;
   }
   return deckMap[deckName];
}
