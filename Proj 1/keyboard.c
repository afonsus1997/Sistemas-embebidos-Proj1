/*
 * keyboard.c
 *
 *  Created on: 02/10/2019
 *      Author: Afonso Muralha
 */

#include "keyboard.h"

char scan_keyboard(){
    char keyboard_mask = 0b00;
    int i = KEYBOARD_SCAN_TIME;
    for(i;i>=0;i--){
         keyboard_mask |= (P1IN >> 3)&1;
         //keyboard_mask |= (((P2IN >> 7)&1)<<1);
    }
    return keyboard_mask;
}

