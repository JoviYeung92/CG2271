#include <Arduino.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#define STACK_SIZE     200
#define TICKS_TO_WAIT  (TickType_t) 1500

QueueHandle_t xQueue;

void serialPrint(void *p) {
	while (1) {
		/*receive taskNum from message queue */
		int taskNum;
		xQueueReceive(xQueue, &taskNum, TICKS_TO_WAIT);
		Serial.print("Task ");
		Serial.println(taskNum);
	}
}

void task1and2(void *p) {
	while (1) {
		int taskNum = (int) p;
		/* send taskNum to message queue */
		xQueueSend(xQueue, &taskNum, TICKS_TO_WAIT);
		vTaskDelay(1);
	}
}

void setup() {
	Serial.begin(115200);
	xQueue = xQueueCreate(20, sizeof(int));
	if (xQueue == NULL) {
		Serial.print("Unable to create queue.");
	}
}

void loop() {
	// Creates two tasks one with higher priority than the other.
	xTaskCreate(task1and2, "Task1", STACK_SIZE, (void * ) 1, 1, NULL);
	xTaskCreate(task1and2, "Task2", STACK_SIZE, (void * ) 2, 2, NULL);
	xTaskCreate(serialPrint, "Print", STACK_SIZE, NULL, 3, NULL);

	// Starts scheduler.
	vTaskStartScheduler();
}
