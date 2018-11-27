#ifndef _ACTIONGENERATOR_H_
#define _ACTIONGENERATOR_H_

namespace l5r
{
   class actiongenerator
   {
      public:
         actiongenerator();
         ~actiongenerator();

         choice getChoice(gamestate &gs);
   };
}

#endif //_ACTIONGENERATOR_H_
