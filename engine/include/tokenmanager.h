#ifndef _TOKEN_MANAGER_H_
#define _TOKEN_MANAGER_H_

#include "choice.h"
#include "carddatamanager.h"
#include <memory>
#include <list>
#include <string>

namespace l5r
{
   class tokenstate;
   class tokenManager
   {
      public:
         tokenManager(tokenstate *tokens, std::string name);
         ~tokenManager();

         void setHonor(int honor);
         int getHonor();

         void gainHonor(int honor);
         void loseHonor(int honor);

         void setHonorDial(int honor);
         int getHonorDial();

         void gainFate(int fate);
         void loseFate(int fate);
         int getFate();

         bool dishonorLoss();
         bool honorWin();

      private:
         tokenstate *tokens;
         std::string name;
   };
};
#endif // _TOKEN_MANAGER_H_
