/*
 * time.c
 *
 *  Created on: 02/10/2019
 *      Author: Afonso Muralha
 */

#include "time.h"

short Hour, Minute, Second;


/*#pragma vector = TIMER0_A0_VECTOR
__interrupt void myTimerISR(void)
{
  if (++Second >= 60)
  {
    Second = 0;
    if (++Minute >= 60)
    {
      Minute = 0;
      if (++Hour >=24)
      {
        Hour = 0;
      }
    }
  }
  ShowTime();
}*/

void init_Date_Time(void)
{

  Hour   = 12;
  Minute = 0;
  Second = 0;
}

void showTime(void){
    int _hour = Hour;
    int _minute = Minute;

    WRITE_DISPLAY(1, _hour % 10);
    _hour /= 10;
    WRITE_DISPLAY(0, _hour % 10);
    _hour /= 10;

     /*
     WRITE_DISPLAY(4, _minute % 10);
    _hour /= 10;
    WRITE_DISPLAY(3,  _minute % 10);
    _hour /= 10;
      */


}

