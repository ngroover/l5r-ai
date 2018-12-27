#ifndef _CONFLICT_MANAGER_H_
#define _CONFLICT_MANAGER_H_

#include "gamestate.h"
#include "carddatamanager.h"

namespace l5r
{
   class conflictManager
   {
      public:
         conflictManager(std::shared_ptr<gamestate> state, std::shared_ptr<cardDataManager> cardMgr);
         ~conflictManager();

         std::string getContestedProvince();

      private:
         std::shared_ptr<gamestate> state;
         std::shared_ptr<cardDataManager> cardMgr;
   };
}

#endif //_CONFLICT_MANAGER_H_
