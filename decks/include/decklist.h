#ifndef _DECKLIST_H_
#define _DECKLIST_H_

#include <string>
#include <list>
#include "cards.h"

namespace l5r
{
   class decklist
   {
      public:
         decklist(std::string name, std::list<cards> cardList);
         ~decklist();

         std::string getName();

         std::list<cards> getList();

      private:
         std::string name;
         std::list<cards> cardList;
   };
};

#endif //_DECKLIST_H_
