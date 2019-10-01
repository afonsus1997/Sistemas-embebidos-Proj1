#include <msp430.h>				

volatile unsigned char numMap[10] = {0b0000000, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1100111};
volatile unsigned int pinMap[7] = {0, 1, 2, 4, 5, 0, 1};
volatile unsigned int portMap[7] = {1, 1, 1, 1, 1, 2, 2};
volatile unsigned int latchPinMap[2] = {2,3};
volatile unsigned int latchPortMap[2] = {2,2};


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

    int i=0;
    for(i;i<7;i++)
        GPIO_WRITE(portMap[i], pinMap[i], 0);
    GPIO_WRITE(2,2,0);GPIO_WRITE(2,3,0);
    GPIO_WRITE(2,2,1);GPIO_WRITE(2,3,1);

}

void WRITE_DISPLAY(int display, int number){

        unsigned int i = 0;

        for(i;i<7;i++)
            GPIO_WRITE(portMap[i], pinMap[i], (numMap[number]>>i)&0x1);

        if(display==0){
            GPIO_WRITE(2,2,0);GPIO_WRITE(2,3,1);
        }
        else
            GPIO_WRITE(2,2,1);GPIO_WRITE(2,3,0);
        GPIO_WRITE(2,2,1);GPIO_WRITE(2,3,1);

}


void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	/*P1DIR |= 0x01;					// configure P1.0 as output

	volatile unsigned int i;		// volatile to prevent optimization

	while(1)
	{
		P1OUT ^= 0x01;				// toggle P1.0
		for(i=10000; i>0; i--);     // delay
	}*/

	volatile unsigned int i;
	volatile unsigned int j;
	GPIO_INIT();
	for(j=0;j<10;j++){
	    for(i=100000; i>0; i--);
	    for(i=100000; i>0; i--);// delay
	    for(i=100000; i>0; i--);// delay
	    for(i=100000; i>0; i--);// delay
        WRITE_DISPLAY(1, j);
        WRITE_DISPLAY(0, j);
    //WRITE_DISPLAY(0, 2);
	}
}
