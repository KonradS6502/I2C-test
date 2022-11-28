/* 
 * File:   main.c
 * Author: Konrad Segelyn
 *
 * Created on 27 listopada 2022, 14:10
 */
#define F_CPU 24000000

#include <avr/io.h>
#include "eepromAT24C.h"


void PORTA_conf(void){
    PORTA.PIN2CTRL|=_BV(3);
    PORTA.PIN3CTRL|=_BV(3);
}

void I2C_init(void);

int main(void) {
    I2C_init();
    write_EEPROM(0x1,0xAD);
    while(1){
        GPR.GPR0=read_random_EEPROM(0x100);
        asm("nop");
    }
}


void I2C_init(void){
    TWI0.MBAUD=0xFF;
    TWI0.MCTRLA|=_BV(0);
    TWI0.MSTATUS|=_BV(0);
}

