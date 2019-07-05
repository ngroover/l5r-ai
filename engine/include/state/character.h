#ifndef _CHARACTER_H_
#define _CHARACTER_H_

namespace l5r
{
   // in play characters
   class inplaycharacter
   {
   public:
      inplaycharacter();
      ~inplaycharacter();

      friend bool operator==(const inplaycharacter &ipc, const inplaycharacter &ipc2);
      friend bool operator<(const inplaycharacter &ipc, const inplaycharacter &ipc2);

      int characterCard;
      bool bowed;
      int fateAttached;
   };
   bool operator==(const inplaycharacter &ipc, const inplaycharacter &ipc2);
   bool operator<(const inplaycharacter &ipc, const inplaycharacter &ipc2);
};
#endif // _CHARACTER_H_
