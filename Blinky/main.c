/*
 * Blinky.c
 *
 * Created: 16-Mar-20 09:45:33
 * Author : Edwin
 */ 

#include <avr/io.h>
#include <stdint.h>

void delay(){
    volatile uint16_t i;
    for(i=0; i<0x4FFF; i++){

    }
}

void init_LED(){
    DDRB |= (1<<5);
    PORTB &= ~(1<<5); 
}

int main(void)
{
    // LED_Pin: PB5
    init_LED();

    while (1) 
    {
        PORTB |= (1<<5);
        delay();
        PORTB &= ~(1<<5);
        delay();
    }
}

