/*
 * time.c
 *
 *  Created on: 02/10/2019
 *      Author: Afonso Muralha
 */

#include "time.h"

short Hour, Minute, Second;
char mode = 0b00;
unsigned int temp = 23;

void updateTemp(int RxTemp){
    if(RxTemp!=0)
        temp = (RxTemp>>7)>>1;
}


void init_Date_Time(void)
{

  Hour   = 5;
  Minute = 2;
  Second = 0;

  init_Timer();
}

void showTime(void){
    int _hour = Hour;
    int _minute = Minute;
    int _second = Second; //remove

    WRITE_DISPLAY(3, _minute % 10);
    _minute /= 10;
    WRITE_DISPLAY(1, _minute % 10);
    _minute /= 10;


     WRITE_DISPLAY(2, _hour % 10);
    _hour /= 10;
    WRITE_DISPLAY(0,  _hour % 10);
    _hour /= 10;


}


void printTemp(){
    int _temp = temp;

    WRITE_DISPLAY(2, _temp % 10);
    _temp /= 10;
    WRITE_DISPLAY(0, _temp % 10);
    _temp /= 10;

    WRITE_DISPLAY(1,0);
    WRITE_DISPLAY(3,0);
}

void init_Timer(){
    //P1DIR |= (1 << 4);                    // P1DIR P1.4 -- CLOCK
    //P1SEL |= (1 << 4);                    // P1SEL P1.4 -- CLOCK

    DCOCTL |= 0xE0;                        // DC0 CTL     = 1110 0000
    BCSCTL1 |= 0x87;                    // BCS CTL1     = 1000 0111

    BCSCTL2 |= DIVS_2;                    // SMCLK divided by 2^2=4

    TACTL = TASSEL_2 + MC_1 + ID_3;        // TA0 CTL = 1011 01000
    CCTL0 = CCIE;                        // TA0 CCTL0
    CCR0 = 24198;                        // TA0 CCR0 value is 24198 (0x5E86)
    //if button is not pressed, enable interrupts
    if(!((P1IN >> 3)&1)){

        //while(1);
    }else{
    //TA0CCTL0_bit.CCIE = 1;   // enable timer interrupts
    //__enable_interrupt();    // set GIE in SR
    //__bis_SR_register(LPM0_bits + GIE);
    __bis_SR_register(GIE);
    }
}





#pragma vector = TIMER0_A0_VECTOR
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
  if(mode==0)
      showTime();
  else{
      printTemp();
  }

}


int handleKeyboard(char mask){
    if(mask==0b10 && mode == 0){
        if (++Minute >= 60)
            {
              Minute = 0;
              if (++Hour >=24)
              {
                Hour = 0;
              }
            }
    }
    else if(mask==0b01 && mode==0){
        if (--Minute <= 0)
            {
              Minute = 59;
              if (--Hour <= 0)
              {
                Hour = 24;
              }
            }
    }
    else if(mask == 0b00){
        if(mode==0b00)
            mode = 0b01;
        else
            mode = 0b00;
    }
}






