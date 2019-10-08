#include <msp430.h>
#include "time.h"
#include "keyboard.h"

#define KEYBOARD_BOUNCE_TIME 100000

volatile unsigned char numMap[10] = {0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1100111};
volatile unsigned int pinMap[7] = {0, 1, 2, 4, 5, 0, 1};
volatile unsigned int portMap[7] = {1, 1, 1, 1, 1, 2, 2};
volatile unsigned int latchPinMap[4] = {2, 3, 4, 5};
volatile unsigned int latchPortMap[4] = {2, 2, 2, 2};

unsigned int RxByteCtr;
unsigned int RxWord = 0;


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

    P2SEL &= ~BIT6; P2SEL &= ~BIT7;
    P2DIR &= ~(1 << 6); P2DIR &= ~(1 << 7);
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


void I2C_INIT(){
    P1SEL  |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    P1SEL2 |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
    UCB0CTL1 |= UCSWRST;                      // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2CSA = 0x48;                         // Set slave address
    UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
    IE2 |= UCB0RXIE;                          // Enable RX interrupt
    TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
}



void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    long i;
    volatile unsigned int j;
    GPIO_INIT();
    I2C_INIT();
    init_Date_Time();
    while(1){
        i = KEYBOARD_BOUNCE_TIME;
        for(i;i>=0;i--);
        handleKeyboard(scan_keyboard());

        updateTemp(RxWord);

        RxByteCtr = 2;                          // Load RX byte counter
        UCB0CTL1 |= UCTXSTT;                    // I2C start condition


    }



}

void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCIAB0TX_ISR (void)
{
  RxByteCtr--;                              // Decrement RX byte counter

  if (RxByteCtr)
  {
    RxWord = (unsigned int)UCB0RXBUF << 8;  // Get received byte
    if (RxByteCtr == 1)                     // Only one byte left?
      UCB0CTL1 |= UCTXSTP;                  // Generate I2C stop condition
  }
  else
  {
    RxWord |= UCB0RXBUF;                    // Get final received byte,
                                            // Combine MSB and LSB
    //__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
  }
}



