#include <Arduino.h>

#define PIN_LED1 6
#define PIN_LED2 7
#define PIN_PTTM 0
#define PIN_TOUCH 1

int remap(int val);
int remapTouch(int val);

void setup() {
	pinMode(PIN_LED1, OUTPUT);
	pinMode(PIN_LED2, OUTPUT);
}

void loop() {
	int val_pttm = analogRead(PIN_PTTM);
	int val_touch = analogRead(PIN_TOUCH);

	analogWrite(PIN_LED1, remap(val_pttm));

	digitalWrite(PIN_LED2, HIGH);
	delay(remapTouch(val_touch));
	digitalWrite(PIN_LED2, LOW);
	delay(remapTouch(val_touch));
}

int remap(int val) {
	return val / 1023.0 * 255.0;
}

int remapTouch(int val) {
	return val / 1023.0 * 375.0 + 125;
}
