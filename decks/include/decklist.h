#ifndef _DECKLIST_H_
#define _DECKLIST_H_

#include <string>
#include <vector>
#include <memory>

namespace l5r
{
   class Decklist
   {
      public:
         Decklist(std::string name, std::vector<std::string> cardList);
         ~Decklist();

         std::string getName();

         std::vector<std::string> getList();

      private:
         std::string name;
         std::vector<std::string> cardList;
   };
   typedef std::shared_ptr<Decklist> DecklistSharedPtr;
};

#endif //_DECKLIST_H_
