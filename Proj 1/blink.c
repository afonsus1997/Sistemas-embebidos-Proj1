#include <msp430.h>
#include "time.h"
#include "keyboard.h"

volatile unsigned char numMap[10] = {0b0000000, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1100111};
volatile unsigned int pinMap[7] = {0, 1, 2, 4, 5, 0, 1};
volatile unsigned int portMap[7] = {1, 1, 1, 1, 1, 2, 2};
volatile unsigned int latchPinMap[4] = {2, 3, 4, 5};
volatile unsigned int latchPortMap[4] = {2, 2, 2, 2};


/**
 * blink.c
 */



void GPIO_WRITE(unsigned int port, unsigned int PIN, unsigned int value){
    if(port==1){
        if(value==1)P1OUT &= ~(1 << PIN);
        if(value==0)P1OUT |= (1 << PIN);
    }
    else{
        if(value==1)P2OUT &= ~(1 << PIN);
        if(value==0)P2OUT |= (1 << PIN);
    }
}

void GPIO_INIT(){
    P1DIR |= 0xFFFF;
    P2DIR |= 0xFFFF;

    P1DIR &= ~(1 << 3);
    P1REN |= (1 << 3);
    P1OUT |= (1 << 3);

    P2DIR &= ~(1 << 6);
    P2REN |= (1 << 6);
    P2OUT |= (1 << 6);


    int i=0;
    for(i;i<7;i++)
        GPIO_WRITE(portMap[i], pinMap[i], 0);
    for(i=0; i<4; i++)
        toggleLatch(i);

}

void toggleLatch(int display){

    GPIO_WRITE(latchPortMap[display],latchPinMap[display], 0);
    GPIO_WRITE(latchPortMap[display],latchPinMap[display], 1);

}

void WRITE_DISPLAY(int display, int number){

        unsigned int i = 0;

        for(i;i<7;i++)
            GPIO_WRITE(portMap[i], pinMap[i], (numMap[number]>>i)&0x1);

        toggleLatch(display);
}


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    volatile unsigned int i;
    volatile unsigned int j;
    GPIO_INIT();
    //init_Date_Time();
    //showTime();
    while(1){
        int i = 1000;
        if(scan_keyboard())
            WRITE_DISPLAY(0, 2);

        else
            WRITE_DISPLAY(0, 1);
        //for(i;i>=0;i--);
    }


    //WRITE_DISPLAY(0, 2);


}


