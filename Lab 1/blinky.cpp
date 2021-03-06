/*
* blinky.cpp
*
* Created on: Jan 14, 2016
* Author: Administrator
*/
#include <avr/io.h> // Header file to access Atmega328 I/O registers
#include <Arduino.h> // Header file for the Arduino library
#define GREEN_PIN 12
#define RED_PIN 13

void blink_led(unsigned pinnum) {
	digitalWrite(pinnum, HIGH); // Set digital I/O pin to a 1
	delay(1000); // Delay
	digitalWrite(pinnum, LOW); // Set digital I/O pin to a 0
	delay(1000); // Delay
}

void setup() {
	pinMode(GREEN_PIN, OUTPUT); // Set digital I/O pins 12
	pinMode(RED_PIN, OUTPUT); // and 13 to OUTPUT.
}

void loop () {
	blink_led(RED_PIN);
	blink_led(GREEN_PIN);
	blink_led(GREEN_PIN);
}
