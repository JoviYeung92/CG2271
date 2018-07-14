#define inputPin 0
#define outputPin 5

void loop() {
	int inVal = analogRead(inputPin);
	analogWrite(outputPin, remap(inVal));
}

// Remaps from 0-1023 to 0-255.
int remap(int val) {
	retur (int) (val * 255.0 / 1023.0);
}