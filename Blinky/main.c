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
    ADMUX = (1 << REFS0);
	
	//ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
	ADCSRA = 0;
	
	// free running mode
	ADCSRB = 0;
	
	DIDR0 = 0;
	DIDR0 |= 0x01;
	
	// Pin C0 is high Z input
	DDRC &= ~0x01;
	PORTC &= ~0x01;
	
	
	
	// enable adc
	ADCSRA |= (1 << ADEN);
	
	
}

uint16_t read_ADC()
{
	// Reading ADC value
	// start adc conversion
	ADCSRA |= (1<<ADSC);
	// Checking/waiting until adc value has updated
	
	// wait for conversion completion (poll for ADIF flag)
	while( ADCSRA & (1<<ADSC) );
	
	return ADC;//(uint16_t) ((ADCH << 8) | ADCL);
}

// https://embedds.com/adc-on-atmega328-part-1/

int main(void)
{
	uint16_t adcValue = 0;
	uint8_t check = 0x00;
	
    // LED_Pin: PB5
    init_LED();
    init_ADC();

    
    while (1) 
    {
		
		#if 0
        // Read adc value
        adcValue = ADCH;
        adcValue <<= 8;
        adcValue |= ADCL;
		#endif

		adcValue = read_ADC();
			
        // LED blinking with a frequency that depends on the adc value
        PORTB |= (1<<5);
        delay(adcValue);
        PORTB &= ~(1<<5);
        delay(500);
    }
}

