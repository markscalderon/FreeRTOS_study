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
	xTaskCreate(vTask1, "Task 1",	1000, (void*)pcTextForTask1, 2,NULL );
	/* Create the second task at priority 1, which is lower than the priority given to Task 1. Again, the task parameter is not used so it is set to NULL, but this time the task handle is required so the address of xTask2Handle is passed in the last parameter. */
	xTaskCreate( vTask2, "Task 2", 1000, (void*)pcTextForTask2, 1, &xTask2Handle );
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();
  for( ;; );
	return 0;
}

void vTask1(void *pvParameters )
{
	const char *pcTaskName = (char*) pvParameters;
	UBaseType_t uxPriority;

  /* This task will always run before Task 2 because it is created with the higher priority. Task 1 and Task 2 never block, so both will always be in either the Running or the Ready state. Query the priority at which this task is running. Passing in NULL means "return the calling task's priority". */

  uxPriority = uxTaskPriorityGet( NULL );
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s \n", pcTaskName );
		printf( "About to raise the Task 2 priority\r\n" );
		vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );
		/* Task 1 will only run when it has a priority higher than Task 2. Therefore, for this task to reach this point, Task 2 must already have executed and set its priority back down to below the priority of this task. */

	}
}

void vTask2(void *pvParameters )
{
	const char *pcTaskName = (char*)pvParameters;
	UBaseType_t uxPriority;

  /* Task 1 will always run before this task because Task 1 is created with the higher priority. Task 1 and Task 2 never block so they will always be in either the Running or the Ready state. Query the priority at which this task is running. Passing in NULL means "return the calling task's priority". */
	uxPriority = uxTaskPriorityGet( NULL );
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s \n",pcTaskName );
		/* Set the priority of this task back down to its original value. Passing in NULL as the task handle means "change the priority of the calling task". Setting the priority below that of Task 1 will cause Task 1 to immediately start running again, preempting this task. */

    printf("About to lower the Task 2 priority\r\n" );

    vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
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
	/* This hook function does nothing but increment a counter. */


	return;
}
