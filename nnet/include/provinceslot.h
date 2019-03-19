#ifndef _PROVINCE_SLOT_H_
#define _PROVINCE_SLOT_H_

namespace l5r
{
   struct ProvinceSlot
   {
      // position
      double stronghold;
      double province1;
      double province2;
      double province3;
      double province4;

      //state
      double broken;
      double contested;
   } typedef ProvinceSlot;
}
#endif // _PROVINCE_SLOT_H_
