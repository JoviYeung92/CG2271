#include <Arduino.h>
#include <stdlib.h>
#include <limits.h>

int fun1(int x, int y) {
	return x + y;
}

int fun2(int x, int y) {
	return x * y;
}

void setup() {
	Serial.begin(115200);
}

// Declare a function pointer
int (*funcptr)(int, int);

void loop() {
	float turn=(float)(rand() / INT_MAX);

	if (turn > 0.5) {
		funcptr = fun1;
	} else {
		funcptr = fun2;
	}

	// Invoke the function
	Serial.print("Computation result: %d\n", funcptr(2, 3));

	// 200ms pause
	delay(200);
}
