/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/
 
extern signed long int task1_in_time , task1_out_time , task1_total_time;
extern signed long int task2_in_time , task2_out_time , task2_total_time;
extern signed long int task3_in_time , task3_out_time , task3_total_time;
extern signed long int task4_in_time , task4_out_time , task4_total_time;
extern signed long int task5_in_time , task5_out_time , task5_total_time;
extern signed long int task6_in_time , task6_out_time , task6_total_time;
extern int sys_time ;
extern int CPU_load ;

#define configUSE_PREEMPTION		(1)
#define configUSE_IDLE_HOOK			(1)
#define configUSE_TICK_HOOK			(0)
#define configCPU_CLOCK_HZ			( ( unsigned long ) 60000000 )	/* =12.0MHz xtal multiplied by 5 using the PLL. */
#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES		( 1 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 90 )
#define configTOTAL_HEAP_SIZE		( ( size_t ) 13 * 1024 )
#define configMAX_TASK_NAME_LEN		( 9 )
#define configUSE_TRACE_FACILITY	(1)
#define configUSE_16_BIT_TICKS		(0)
#define configUSE_EDF_SCHEDULER 		(1)
#define configIDLE_SHOULD_YIELD		(1)
#define configUSE_QUEUE_SETS   (1)
#define configUSE_TIME_SLICING    (0)
#define configQUEUE_REGISTRY_SIZE 	(0)
#define configUSE_STATS_FORMATTING_FUNCTIONS  (1) 
#define configGENERATE_RUN_TIME_STATS           (1)  
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE() (T1TC)
#define configUSE_APPLICATION_TASK_TAG (1) 

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		(0)
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		(0)
#define INCLUDE_uxTaskPriorityGet		(0)
#define INCLUDE_vTaskDelete				(0)
#define INCLUDE_vTaskCleanUpResources	(0)
#define INCLUDE_vTaskSuspend			(0)
#define INCLUDE_vTaskDelayUntil			(1)
#define INCLUDE_vTaskDelay				(1)



#define traceTASK_SWITCHED_OUT()      do \
																			 {\
																				 if((int)pxCurrentTCB->pxTaskTag == 1)\
																				 {\
																					 GPIO_write(PORT_0,PIN3,PIN_IS_LOW);\
																					 task1_out_time	=	T1TC;\
																			  	 task1_total_time += (task1_out_time - task1_in_time);\
																				 }\
																				 else if((int)pxCurrentTCB->pxTaskTag == 2)\
																				 {\
																					 GPIO_write(PORT_0,PIN4,PIN_IS_LOW);\
																					 task2_out_time	=	T1TC;\
																			  	 task2_total_time += (task2_out_time - task2_in_time);\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 3)\
																				 {\
																					 GPIO_write(PORT_0,PIN5,PIN_IS_LOW);\
																					 task3_out_time	=	T1TC;\
																			  	 task3_total_time += (task3_out_time - task3_in_time);\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 4)\
																				 {\
																					 GPIO_write(PORT_0,PIN1,PIN_IS_LOW);\
																					 task4_out_time	=	T1TC;\
																			  	 task4_total_time += (task4_out_time - task4_in_time);\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 5)\
																				 {\
																					 GPIO_write(PORT_0,PIN7,PIN_IS_LOW);\
																					 task5_out_time	=	T1TC;\
																			  	 task5_total_time += (task5_out_time - task5_in_time);\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 6)\
																				 {\
																					 GPIO_write(PORT_0,PIN8,PIN_IS_LOW);\
																					 task6_out_time	=	T1TC;\
																			  	 task6_total_time += (task6_out_time - task6_in_time);\
																				 }\
																				 sys_time = 	T1TC;\
																				 CPU_load = ((task1_total_time + task2_total_time + task3_total_time + task4_total_time + task5_total_time + task6_total_time) / (float) sys_time) * 100;\
																   		 }\
																			 while(0)

#define traceTASK_SWITCHED_IN()				 do \
																			 {\
																				 if((int)pxCurrentTCB->pxTaskTag == 1)\
																				 {\
      																	 GPIO_write(PORT_0,PIN3,PIN_IS_HIGH);\
																					 task1_in_time	=	T1TC;\
																				 }\
																				 else if((int)pxCurrentTCB->pxTaskTag == 2)\
																				 {\
																					 GPIO_write(PORT_0,PIN4,PIN_IS_HIGH);\
																					 task2_in_time	=	T1TC;\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 3)\
																				 {\
																					 GPIO_write(PORT_0,PIN5,PIN_IS_HIGH);\
																					 task3_in_time	=	T1TC;\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 4)\
																				 {\
																					 GPIO_write(PORT_0,PIN1,PIN_IS_HIGH);\
																					 task4_in_time	=	T1TC;\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 5)\
																				 {\
																					 GPIO_write(PORT_0,PIN7,PIN_IS_HIGH);\
																					 task5_in_time	=	T1TC;\
																				 }\
																				  else if((int)pxCurrentTCB->pxTaskTag == 6)\
																				 {\
																					 GPIO_write(PORT_0,PIN8,PIN_IS_HIGH);\
																					 task6_in_time	=	T1TC;\
																				 }\
																   		 }\
																			 while(0)

															
#endif /* FREERTOS_CONFIG_H */
