//delay with until
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#define mainDELAY_LOOP_COUNT		( 0xfffff )

void vTask1(void *pvParameters );
void vTask2(void *pvParameters );
static const char *pcTextForTask1 = "Task 1 is running\r\n";
static const char *pcTextForTask2 = "Task 2 is running\r\n";

int main()
{

	/* Create the first task at priority 1. The priority is the second to last
parameter. */
	xTaskCreate(vTask1, "Task 1",	1000, (void*)pcTextForTask1, 1,NULL );
	/* Create the other task in exactly the same way and at the same priority. */
	xTaskCreate( vTask2, "Task 2", 1000, (void*)pcTextForTask2, 2, NULL );
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();
  for( ;; );
	return 0;
}

void vTask1(void *pvParameters )
{
	const char *pcTaskName = (char*) pvParameters;
	TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialized with the current tick
count. Note that this is the only time the variable is written to explicitly.
After this xLastWakeTime is automatically updated within vTaskDelayUntil(). */
  xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s\n", pcTaskName );
		/* This task should execute every 250 milliseconds exactly. As per
		the vTaskDelay() function, time is measured in ticks, and the
		pdMS_TO_TICKS() macro is used to convert milliseconds into ticks.
		xLastWakeTime is automatically updated within vTaskDelayUntil(), so is not
		explicitly updated by the task. */
		vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 250 ) );
	}
}

void vTask2(void *pvParameters )
{
	const char *pcTaskName = (char*)pvParameters;
	TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialized with the current tick
count. Note that this is the only time the variable is written to explicitly.
After this xLastWakeTime is automatically updated within vTaskDelayUntil(). */
  xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s\n",pcTaskName );
		/* This task should execute every 250 milliseconds exactly. As per
		the vTaskDelay() function, time is measured in ticks, and the
		pdMS_TO_TICKS() macro is used to convert milliseconds into ticks.
		xLastWakeTime is automatically updated within vTaskDelayUntil(), so is not
		explicitly updated by the task. */
		vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 250 ) );
	}
}
/********************************************************/
/* This is a stub function for FreeRTOS_Kernel */
void vMainQueueSendPassed( void )
{
	return;
}

/* This is a stub function for FreeRTOS_Kernel */
void vApplicationIdleHook( void )
{
	return;
}
