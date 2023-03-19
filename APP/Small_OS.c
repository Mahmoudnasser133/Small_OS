/*
 * Small_OS.c
 *
 *  Created on: Mar 5, 2023
 *      Author: nasser
 */


#include <avr/delay.h>
#include "STD_TYPES.h"
#include "Port_int.h"
#include "Dio_int.h"
#include "Led_int.h"
//#include "SSD_int.h"
//#include "Mcu_HW.h"
//#include "BIT_MATH.h"
#include "PB_int.h"
//#include "Lcd_int.h"
//#include "Keypad_int.h"
//#include "Exti_int.h"
#include "Glint.h"
#include "Timer_int.h"
#include "Timer1_int.h"


void Task_One_toggel_Yellow(void);
void Task_Two_toggel_BLUE(void);
void Task_Three_toggel_Green(void);
void Scheduler(void);


extern const Port_ConfigType PORT_Config_Arr[PORT_PINS_CONFIG_ARR_SIZE];

Timer0_config Timer0_config_struct1={prescaler_1024,CTC_mode,normal};

volatile u8 Scheduler_counter=0;


int main()
{
Port_Init(PORT_Config_Arr);
H_LCD_void_Init();



Enable_Global_INT();

M_Timer0_void_Init(&Timer0_config_struct1);

M_Timer0_void_Enable_INT(CMP_INT_ID);

M_Timer0_void_setCallBack(Scheduler);

M_Timer0_void_start(Timer0_config_struct1.prescaler_value);

M_Timer0_void_setDelayTimeMilliSec(&Timer0_config_struct1, 500);


while(1)
{

}






return 0;
}

void Task_One_toggel_Yellow(void)
{
	H_LED_void_toggle(LED_YELLOW);
}
void Task_Two_toggel_BLUE(void)
{
	if (H_PB_u8_Read(PB1_ID) == PB_PREESED)
	{
		H_LED_void_toggle(LED_BLUE);
	}

}
void Task_Three_toggel_Green(void)
{
	H_LED_void_toggle(LED_GRN);
}

void Scheduler(void)
{
	if(Scheduler_counter == 0)
	{
		Task_One_toggel_Yellow();
		Task_Two_toggel_BLUE();
		Task_Three_toggel_Green();
	}


	if(Scheduler_counter == 2 || Scheduler_counter == 4 )
	{
		Task_One_toggel_Yellow();
		Task_Two_toggel_BLUE();
	}

	if(Scheduler_counter == 6 )
		{
		  Task_One_toggel_Yellow();
		  Task_Two_toggel_BLUE();
		  Task_Three_toggel_Green();
		  Scheduler_counter = 1;
		}
	else
	{
		Task_Two_toggel_BLUE();
	}
	Scheduler_counter++;
}




