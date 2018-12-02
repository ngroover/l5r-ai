#ifndef _DECISION_H_
#define _DECISION_H_

#include <string>
#include <list>
#include "choice.h"

namespace l5r
{
   class decision
   {
      public:
         decision(std::string prompt, std::list<choice> choiceList);
         decision(){};
         ~decision();

         std::list<choice> &getChoiceList();
         std::string &getPrompt();

      private:
         std::string prompt;
         std::list<choice> choiceList;
   };
}

#endif //_DECISION_H_
