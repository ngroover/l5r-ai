#ifndef _TOKENS_H_
#define _TOKENS_H_

namespace l5r
{
   class tokenstate
   {
      public:
         tokenstate();
         ~tokenstate();

         friend bool operator==(const tokenstate &ts, const tokenstate &ts2);
         friend bool operator<(const tokenstate &ts, const tokenstate &ts2);

         int honorTokens;
         int fate;
         int honorDial;
   };

   bool operator==(const tokenstate &ts, const tokenstate &ts2);
   bool operator<(const tokenstate &ts, const tokenstate &ts2);
};

#endif // _TOKENS_H_
