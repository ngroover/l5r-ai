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

      private:
         std::string text;
         choicetype type;
         cards targetCard;

   };
};

#endif //_CHOICE_H_
