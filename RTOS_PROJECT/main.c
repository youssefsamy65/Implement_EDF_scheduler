/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "queue.h"
#include "FreeRTOSConfig.h"
/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"
/*-----------------------------------------------------------*/
#define HIGH 1
#define LOW  0
 int sys_time ;
 int CPU_load ;
/*-----------------------------------------------------------*/
signed long int task1_in_time , task1_out_time , task1_total_time;
signed long int task2_in_time , task2_out_time , task2_total_time;
signed long int task3_in_time , task3_out_time , task3_total_time;
signed long int task4_in_time , task4_out_time , task4_total_time;
signed long int task5_in_time , task5_out_time , task5_total_time;
signed long int task6_in_time , task6_out_time , task6_total_time;
/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )
/*-----------------------------------------------------*/

struct AMessage
{
   char ucMessageID;
   char ucData[ 20 ];
}xMessage;

QueueHandle_t xQueue1 = NULL;/* Queue handle */
TaskHandle_t task__1 = NULL; /* tasks handle */
TaskHandle_t task__2 = NULL;
TaskHandle_t task__3 = NULL;
TaskHandle_t task__4 = NULL;
TaskHandle_t task__5 = NULL;
TaskHandle_t task__6 = NULL;
TickType_t xLastWakeTime =NULL ;
void task_1( void * pvParameters  ){
int state = LOW ;
struct AMessage pxMessage;
pxMessage.ucMessageID = 0xab;
vTaskSetApplicationTaskTag( NULL, (void *) 1);
	for(;;)
{
xLastWakeTime = xTaskGetTickCount();
	if ( (  GPIO_read(  PORT_1 , PIN0) == PIN_IS_HIGH )&&( state == LOW)) {
    /*Rising edge detected*/
		state = HIGH; // Record current state
    sprintf(pxMessage.ucData,"high_button1");
xQueueSend( xQueue1, ( void * ) &pxMessage, ( TickType_t ) 0 );
}
else if ((GPIO_read(  PORT_1 , PIN0) == PIN_IS_LOW )&& (state == HIGH)) {
    /*falling edge detected*/
    state = LOW; // Record current state
sprintf(pxMessage.ucData,"low_button1");
xQueueSend(  xQueue1,( void * ) &pxMessage, ( TickType_t ) 0 );
}
vTaskDelayUntil(&xLastWakeTime,50);
}

}

void task_2( void * pvParameters  ){
int state1 = LOW ;
struct AMessage pxMessage1;
pxMessage1.ucMessageID = 0xa0;
vTaskSetApplicationTaskTag( NULL, (void *) 2);
for(;;)
{
  xLastWakeTime = xTaskGetTickCount();
	if ( (  GPIO_read(  PORT_1 , PIN1) == PIN_IS_HIGH )&&( state1 == LOW)) {

    state1 = HIGH; // Record current state.
    sprintf(pxMessage1.ucData,"high_button2");
xQueueSend( xQueue1,( void * ) &pxMessage1,( TickType_t ) 0 );
	}
 else if ((GPIO_read(  PORT_1 , PIN1) == PIN_IS_LOW )&& (state1 == HIGH)) {
    // Falling edge detected!
state1 = LOW; // Record current state.
sprintf(pxMessage1.ucData,"low_button2");
xQueueSend( xQueue1,( void * ) &pxMessage1,( TickType_t ) 0 );
}
vTaskDelayUntil(&xLastWakeTime,50);
}
}
void task_3( void * pvParameters  )
{
struct AMessage pxMessage2;
pxMessage2.ucMessageID = 'Q';
vTaskSetApplicationTaskTag( NULL, (void *) 3);
for(;;){
xLastWakeTime = xTaskGetTickCount();
sprintf(pxMessage2.ucData,"periodic_string");
xQueueSend(  xQueue1, ( void * ) &pxMessage2,( TickType_t ) 0 );
vTaskDelayUntil(&xLastWakeTime,100);
}
}
void task_4( void * pvParameters  ){
struct  AMessage TX1;
for(;;){
 xLastWakeTime = xTaskGetTickCount();
 xQueueReceive( xQueue1,&( TX1 ),( TickType_t )0);
 vSerialPutString((signed char * )(TX1.ucData) ,20);
xSerialPutChar((signed char)(TX1.ucMessageID) );
	vTaskDelayUntil(&xLastWakeTime,100);
}
}
void task_5( void * pvParameters  ){
signed long int i;
vTaskSetApplicationTaskTag( NULL, (void *) 5);
	for(;;){
xLastWakeTime = xTaskGetTickCount();
		for( i = 0;i < 38000;)	// excute for 5 ms
		{
			i++;
		}
vTaskDelayUntil(&xLastWakeTime,10);
}
}
void task_6( void * pvParameters  ){
 signed long int i ;
vTaskSetApplicationTaskTag( NULL, (void *) 6);
xLastWakeTime = xTaskGetTickCount();
	for(;;){

		for( i = 0;i < 97000;)	//excute for 12 ms
		{
i++;
		}
vTaskDelayUntil(&xLastWakeTime,100);
}
   }
void vApplicationIdleHook(void)
{

	GPIO_write(PORT_0, PIN2, PIN_IS_HIGH);
	GPIO_write(PORT_0, PIN2, PIN_IS_LOW);
}


/*-----------------------------------------------------*/
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/
int main( void )
{

	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();
xQueue1 = xQueueCreate(5, sizeof(xMessage));
    /* Create Tasks here */
 xTaskCreatePeriodic(
                    task_1,       /* Function that implements the task. */
                    "Button_1_Monitor",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &task__1,50);      /* Used to pass out the created task's handle. */
xTaskCreatePeriodic(
                    task_2,       /* Function that implements the task. */
                    "Button_2_Monitor",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &task__2,50);
xTaskCreatePeriodic(
                    task_3,       /* Function that implements the task. */
                    "Periodic_Transmitter",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &task__3,100);
xTaskCreatePeriodic(
                    task_4,       /* Function that implements the task. */
                    "Uart_Receiver",          /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
										&task__4,
										20);
xTaskCreatePeriodic(
                    task_5,       /* Function that implements the task. */
                     "Load_1_Simulation",      /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
										&task__5,
										10);
xTaskCreatePeriodic(
                    task_6,       /* Function that implements the task. */
                     "Load_2_Simulation",      /* Text name for the task. */
                    100,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
										&task__6,
										100);
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();

	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/
