#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>

#define STACK_SIZE 200

#define LED_PIN_1 6
#define LED_PIN_2 7
#define LED_PIN_3 8
#define LED_PIN_4 9

#define PERIOD_TASK1  5000U
#define PERIOD_TASK2 10000U
#define PERIOD_TASK3 10000U
#define PERIOD_TASK4 20000U

#define WCET_TASK1   1500U
#define WCET_TASK2   2500U
#define WCET_TASK3   1700U
#define WCET_TASK4    700U

#define MINOR_CYCLE   5000
#define HYPER_CYCLE	 20000

void myDelay(int ms) {
	for (int i = 0; i < ms; i++) {
		delayMicroseconds(1000);
	}
}

void emulateWCET(unsigned int TASK_WCET, unsigned int pin) {
	unsigned int count = 0;
	while (count < TASK_WCET) {
		digitalWrite(pin, HIGH);
		myDelay(50);
		digitalWrite(pin, LOW);
		myDelay(50);
		count += 100;
	}
}

void task1(void *p) {
	emulateWCET(WCET_TASK1, LED_PIN_1);
}

void task2(void *p) {
	emulateWCET(WCET_TASK2, LED_PIN_2);
}

void task3(void *p) {
	emulateWCET(WCET_TASK3, LED_PIN_3);
}

void task4(void *p) {
	emulateWCET(WCET_TASK4, LED_PIN_4);
}

void taskMain(void *p) {
	portTickType initialTick;

	while (1) {
		initialTick = xTaskGetTickCount();
		task1(NULL);
		task2(NULL);
		task4(NULL);
		vTaskDelayUntil(&initialTick, MINOR_CYCLE);

		task1(NULL);
		task3(NULL);
		vTaskDelayUntil(&initialTick, MINOR_CYCLE);

		task1(NULL);
		task2(NULL);
		vTaskDelayUntil(&initialTick, MINOR_CYCLE);

		task1(NULL);
		task3(NULL);
		vTaskDelayUntil(&initialTick, MINOR_CYCLE);
	}
}

void setup() {
	pinMode(LED_PIN_1, OUTPUT);
	pinMode(LED_PIN_2, OUTPUT);
	pinMode(LED_PIN_3, OUTPUT);
	pinMode(LED_PIN_4, OUTPUT);
}

void loop() {
	xTaskCreate(taskMain, "TaskMain", STACK_SIZE, NULL, 1, NULL);
	vTaskStartScheduler();
}
