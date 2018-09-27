//set priority
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

/* Declare a variable that is used to hold the handle of Task 2. */

TaskHandle_t xTask2Handle = NULL;
int main()
{

	/* Create the first task at priority 1. The priority is the second to last
parameter. */
	xTaskCreate(vTask1, "Task 1",	1000, (void*)pcTextForTask1, 1,NULL );
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();
  for( ;; );
	return 0;
}
void vTask1(void *pvParameters )
{
	const char *pcTaskName = (char*) pvParameters;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s \n", pcTaskName );
    /* Create task 2 at a higher priority. Again, the task parameter is not used so it is set to NULL, but this time the task handle is required so the address of xTask2Handle is passed as the last parameter. */
    xTaskCreate( vTask2, "Task 2", 1000, (void*)pcTextForTask2, 2, &xTask2Handle );
    /* The task handle is the last parameter _____^^^^^^^^^^^^^ */
    /* Task 2 has/had the higher priority, so for Task 1 to reach here, Task 2 must have already executed and deleted itself. Delay for 100 milliseconds. */

    vTaskDelay( 100 );
	}
}

void vTask2(void *pvParameters )
{
  printf("Task 2 is running and about to delete itself\r\n");
  vTaskDelete( xTask2Handle );
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
	/* This hook function does nothing but increment a counter. */


	return;
}
