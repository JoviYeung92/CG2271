#define BITO_MASK 0x01

int main() {
	unsigned char* portDDRB;
	unsigned char* portDataB;
	unsigned char* portPinB;

	// Set address
	portDDRB = (unsigned char *) 0x24;
	portDataB = (unsigned char *) 0x25;
	portPinB = (unsigned char *) 0x23;

	// COnfigure only bit 0 as input pin
	*portDDRB = (*portDDRB) & (~BITO_MASK);

	loop();

	return 0;
}

void loop() {
	unsigned char previous, current;

	// Only retrieve bit 0.
	current = (*portPinB) & BITO_MASK;

	if (current != previous) {
		// Do something here.
	}
	previous = current;
}