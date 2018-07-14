#include <Arduino.h>
#include "prioq.h"

#define PIN_INT0 	2
#define PIN_INT1 	3
#define PIN_LED0	7
#define PIN_LED1	6

// Declares a new type called "funcptr"
typedef void (*funcptr)(void);

TPrioQueue *queue;
unsigned long lastTime1;
unsigned long lastTime2;

// Flashes LED at pin 7: 5 times a 4 Hz
void int0task() {
	for(int i = 0; i < 5; i++) {
		digitalWrite(PIN_LED0, HIGH);
		delay(125);
		digitalWrite(PIN_LED0, LOW);
		delay(125);
	}
}

// Flashes LED at pin 6: 5 times at 2HZ
void int1task() {
	for(int i = 0; i < 5; i++) {
		digitalWrite(PIN_LED1, HIGH);
		delay(250);
		digitalWrite(PIN_LED1, LOW);
		delay(250);
	}
}

// ISR for first pushbutton.
void int0ISR() {
	unsigned long cur = millis();
	if (cur - lastTime1 > 200) {
		lastTime1 = cur;
		enq(queue, (void *) int0task, 0);
	}
}

// ISR for second pushbutton.
void int1ISR() {
	unsigned long cur = millis();
	if (cur - lastTime2 > 200) {
		lastTime2 = cur;
		enq(queue, (void *) int1task, 1);
	}
}

// Setup, initialization and attach ISRs.
void setup() {
	queue = makeQueue();

	pinMode(PIN_INT0, INPUT);
	pinMode(PIN_INT1, INPUT);
	pinMode(PIN_LED0, OUTPUT);
	pinMode(PIN_LED1, OUTPUT);

	attachInterrupt(0, int0ISR, FALLING);
	attachInterrupt(1, int1ISR, FALLING);

	lastTime1 = lastTime2 = millis();
}

// Dequeues and calls functions if the queue is not empty
void loop() {
	if (qlen(queue) > 0) {
		funcptr x = (funcptr) deq(queue);
		x();
	}
}
