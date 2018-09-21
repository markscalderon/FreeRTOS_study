#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#define mainDELAY_LOOP_COUNT		( 0xfffff )


void ATaskFunction( void *pvParameters );
void vTask1(void *pvParameters );
void vTask2(void *pvParameters );

static volatile unsigned short usTaskCheck[ 2 ] = { ( unsigned short ) 0 };


int main()
{

	/* Create one of the two tasks. Note that a real application should check
	the return value of the xTaskCreate() call to ensure the task was created
	successfully. */
	xTaskCreate(
		vTask1, /* Pointer to the function that implements the task. */
		"Task 1",/* Text name for the task. This is to facilitate debugging
		only. */
		1000, /* Stack depth - most small microcontrollers will use much
		less stack than this. */
		NULL, /* We are not using the task parameter. */
		1,/* This task will run at priority 1. */
		NULL ); /* We are not going to use the task handle. */
	/* Create the other task in exactly the same way and at the same priority. */
	xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );
	/* Start the scheduler so the tasks start executing. */
	vTaskStartScheduler();
	/* If all is well then main() will never reach here as the scheduler will
	now be running the tasks. If main() does reach here then it is likely that
	there was insufficient heap memory available for the idle task to be created.
	CHAPTER 5 provides more information on memory management. */
	for( ;; );
	return 1;
}

void ATaskFunction( void *pvParameters )
{
	/* Variables can be declared just as per a normal function. Each instance
	of a task created using this function will have its own copy of the
	iVariableExample variable. This would not be true if the variable was
	declared static – in which case only one copy of the variable would exist
	and this copy would be shared by each created instance of the task. */
	int iVariableExample = 0;
	/* A task will normally be implemented as in infinite loop. */
	for( ;; )
	{
		/* The code to implement the task functionality will go here. */
		printf("Hello world\n");
	}
	/* Should the task implementation ever break out of the above loop
	then the task must be deleted before reaching the end of this function.
	The NULL parameter passed to the vTaskDelete() function indicates that
	the task to be deleted is the calling (this) task. */
	vTaskDelete( NULL );
}

void vTask1(void *pvParameters )
{
	const char *pcTaskName = "Task 1 is running\r\n";
	volatile unsigned long ul;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s\n", pcTaskName );
		/* Delay for a period. */
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}
	}
}

void vTask2(void *pvParameters )
{
	const char *pcTaskName = "Task 2 is running\r\n";
	volatile unsigned long ul;
	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		printf("%s\n",pcTaskName );
		/* Delay for a period. */
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}
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
