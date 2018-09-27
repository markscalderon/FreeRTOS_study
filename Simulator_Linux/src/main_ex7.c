//task to delete
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#define mainDELAY_LOOP_COUNT		( 0xfffff )

void vContinuousProcessingTask1(void *pvParameters );
void vContinuousProcessingTask2(void *pvParameters );

void vPeriodicTask(void *pvParameters );
static const char *pcTextForTask1 = "Continuous task 1 running\r\n";
static const char *pcTextForTask2 = "Continuous task 2 running\r\n";
static const char *pcTextForPeriodic = "Periodic task is running\r\n";

void vPrintString( const char *pcString )
{

        /* Write the string to stdout, using a critical section as a crude method of mutual exclusion. */

        taskENTER_CRITICAL();
        {
            printf( "%s", pcString );
            fflush( stdout );
        }
        taskEXIT_CRITICAL();

}

int main()
{

	/* Create the first task at priority 1. The priority is the second to last
parameter. */
	xTaskCreate(vContinuousProcessingTask1, "Task 1",	1000, (void*)pcTextForTask1, 1,NULL );
	xTaskCreate(vContinuousProcessingTask2, "Task 2",	1000, (void*)pcTextForTask2, 1,NULL );

	/* Create the other task in exactly the same way and at the same priority. */
	xTaskCreate(vPeriodicTask, "Periodic", 1000, (void*)pcTextForPeriodic, 3, NULL );
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();
  for( ;; );
	return 0;
}

void vContinuousProcessingTask1(void *pvParameters )
{
	const char *pcTaskName = (char*) pvParameters;
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );
	}
}
void vContinuousProcessingTask2(void *pvParameters )
{
	const char *pcTaskName = (char*) pvParameters;
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );
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
		vPrintString( pcTaskName );
		vTaskDelayUntil( &xLastWakeTime, xDelay3ms );
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
