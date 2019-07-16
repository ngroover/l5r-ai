#ifndef _CARD_DATA_MANAGER_H_
#define _CARD_DATA_MANAGER_H_

#include <memory>
#include "cardgenerator.h"
#include "carddata.h"
#include "state/gamestate.h"

namespace l5r
{
   class cardDataManager
   {
      public:
         cardDataManager(std::shared_ptr<gamestate> state);
         ~cardDataManager();


         CardSharedPtr getCard(std::string id);

      private:
         std::shared_ptr<gamestate> state;

         cardgenerator cg;
   };
};

#endif // _CARD_DATA_MANAGER_H_
