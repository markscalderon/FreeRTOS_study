//task to delete
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#define mainDELAY_LOOP_COUNT		( 0xfffff )

void vContinuousProcessingTask(void *pvParameters );
void vPeriodicTask(void *pvParameters );
static const char *pcTextForTask1 = "Continuous processing is running\r\n";
static const char *pcTextForTask2 = "Periodic task is running\r\n";

int main()
{

	/* Create the first task at priority 1. The priority is the second to last
parameter. */
	xTaskCreate(vContinuousProcessingTask, "Task 1",	1000, (void*)pcTextForTask1, 1,NULL );
	/* Create the other task in exactly the same way and at the same priority. */
	xTaskCreate(vPeriodicTask, "Task 2", 1000, (void*)pcTextForTask2, 1, NULL );
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();
  for( ;; );
	return 0;
}

void vContinuousProcessingTask(void *pvParameters )
{
	const char *pcTaskName = (char*) pvParameters;
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s\n", pcTaskName );
	}
}

void vPeriodicTask(void *pvParameters )
{
	const char *pcTaskName = (char*)pvParameters;
	TickType_t xLastWakeTime;
	const TickType_t xDelay3ms = pdMS_TO_TICKS( 3 );
  xLastWakeTime = xTaskGetTickCount();
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s\n",pcTaskName );
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
