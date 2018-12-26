#ifndef _CHOICE_H_
#define _CHOICE_H_

#include <vector>
#include <string>
#include "cards.h"
#include "gamestate.h"

namespace l5r
{
   enum class choicetype
   {
      card,
      ring,
      bid,
      fate,
      province_play,
      province_attack,
      conflict_type,
      pass
   };

   class choice
   {
      public:
         choice(std::string text, choicetype type);
         ~choice();

         std::string getText() const;
         choicetype getType() const;

         void setNumber(int number);
         int getNumber() const;

         void setChosenRing(ring chosen);
         ring getChosenRing() const;

         void setConflictType(conflicttype type);
         conflicttype getConflictType() const;

      private:
         std::string text;
         choicetype type;
         cards targetCard;
         int number;
         ring chosenring;
         conflicttype conflictType;
   };
};

#endif //_CHOICE_H_
