#ifndef _CHOICE_H_
#define _CHOICE_H_

#include <vector>
#include <string>
#include "cards.h"

namespace l5r
{
   enum class choicetype
   {
      card,
      ring,
      bid,
      fate,
      province_play,
      pass
   };

   class choice
   {
      public:
         choice(std::string text, choicetype type);
         ~choice();

         std::string getText() const;
         choicetype getType() const;

         void setTargetCard(cards target);
         cards getTargetCard() const;

         void setNumber(int number);
         int getNumber() const;

      private:
         std::string text;
         choicetype type;
         cards targetCard;
         int number;
   };
};

#endif //_CHOICE_H_
