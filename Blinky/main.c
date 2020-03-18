/*
 * Blinky.c
 *
 * Created: 16-Mar-20 09:45:33
 * Author : Edwin
 */ 

#include <avr/io.h>
#include <stdint.h>

void delay(uint16_t n){
    volatile uint16_t i;
    for(i=0; i<n; i++){
        // Delay depends on n
    }
}

void init_LED(){
    DDRB |= (1<<5);
    PORTB &= ~(1<<5); 
}

void init_ADC(){
    // Using AVCC with external capacitor at AREF pin (Connect capacitor -> AREF Pin20)
    // Leaving the ADC value right adjusted
    // Setting the MUX to ADC0
    ADMUX = 0x40;
    // Enabling the ADC
    ADCSRA = 0;
    ADCSRA |= (1<<7);
}

int main(void)
{
    // LED_Pin: PB5
    init_LED();
    init_ADC();

    uint16_t adcValue = 0;
    
    while (1) 
    {
        // Reading ADC value
        ADCSRA |= (1<<6);
        // Checking/waiting until adc value has updated
        uint8_t check = 0x00;
        while(check != 0x10){
            // Masking for adc value check
            check = ADCSRA & 0x10;
            // waiting
        }
        // Read adc value
        adcValue = ADCH;
        adcValue <<= 8;
        adcValue |= ADCL;

        // LED blinking with a frequency that depends on the adc value
        PORTB |= (1<<5);
        delay(adcValue);
        PORTB &= ~(1<<5);
        delay(adcValue);
    }
}

