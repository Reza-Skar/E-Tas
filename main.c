#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

ISR(TIM0_OVF_vect) {
}

void mydelay(int ms) {
    for (int i = 0; i < ms; i++) {
        _delay_ms(50);
    }
}

void main(void) 
{
    int LEDs[6] = {0x0E, 0x0B, 0x0A, 0x09, 0x02, 0x01} , a; 
    DDRB = 0x0F; // PB[0-3] : Output(LEDs) , PB[4] : Input(Button)
    /*
        PB1     PB2     PB3

                PB0

        PB3     PB2     PB1    
    */
    PORTB = 0xF0;

    TCCR0B |= (1<<CS02) | (1<<CS00); 
    TIMSK0 |= (1<<TOIE0); 
    sei();    

    while (1) {
        srand(TCNT0);
        if (!(PINB & (1<<PB4))) {
            for (int i = 4; i < 15; i++) {
                PORTB = (0xF0 | LEDs[rand() % 6]);
                mydelay(i);
            }
            a = rand()%6;
            PORTB = (0xF0 | LEDs[a]);
            mydelay(14);
            for (int i = 0; i < 4; i++)
            {
                _delay_ms(300);
                PORTB = 0xF0;
                _delay_ms(300);
                PORTB = (0xF0 | LEDs[a]);
            }
            while (!(PINB & (1<<PB4)))      continue;
        }
    }
}