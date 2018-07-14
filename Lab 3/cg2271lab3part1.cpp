#include <Arduino.h>

#define PIN_INT0  2
#define PIN_INT1  3


void myDelay(int ms) {
	for (int i = 0; i < ms; i++) {
		 delayMicroseconds(1000);
	}
}

void isr0() {
	

    /* switch de-bouncing */
	
		
	/* Flash LED */	

}


void isr1() {


    /* switch de-bouncing */
	
    /* re-enable global interrupts */
	interrupts();
	
	/* Flash LED */

}


void setup() {
	attachInterrupt(digitalPinToInterrupt(PIN_INT0), isr0, RISING);
	attachInterrupt(digitalPinToInterrupt(PIN_INT1), isr1, RISING);
}

void loop() {
}
