#ifndef _END_GAME_EXCEPTION_H_
#define _END_GAME_EXCEPTION_H_

#include <iostream>
#include <exception>

namespace l5r
{
   enum class wintype
   {
      dishonor,
      honor,
      conquest
   };

   class EndGameException : public std::exception
   {
      public:
         EndGameException(wintype type);
         ~EndGameException();

      private:
         wintype type;

         wintype getType();
   };
};

#endif // _END_GAME_EXCEPTION_H_
