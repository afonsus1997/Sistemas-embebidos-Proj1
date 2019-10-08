/*
 * time.h
 *
 *  Created on: 02/10/2019
 *      Author: Afonso Muralha
 */

#ifndef TIME_H_
#define TIME_H_


#include <msp430.h>


void showTime(void);
void init_Date_Time(void);
void init_Timer();
int handleKeyboard(char mask);
void updateTemp(int RxTemp);



#endif /* TIME_H_ */
