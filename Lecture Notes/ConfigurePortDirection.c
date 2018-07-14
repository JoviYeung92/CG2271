int main() {
	unsigned char* portDDRB;

	// Set port address
	portDDRB = (unsigned char *) 0x24;

	// Write DDRB register to set PortB as input port
	*portDDRB = 0;

	return 0;
}