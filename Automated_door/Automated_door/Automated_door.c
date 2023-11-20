/*
 * Automated_door.c
 *
 * Created: 11/1/2023 2:04:26 PM
 *  Author: MERNA
 */ 

/* UTIL Libraries */
#include "UTIL/STD_TYPES.h"
#define F_CPU				16000000UL
#include "util/delay.h"

/* MCAL */
#include "MCAL/DIO/DIO_INTERFACE.h"
#include "MCAL/PORT/PORT_INTERFACE.h"

/* HAL */
#include "HAL/LCD/LCD_INTERFACE.h"
#include "HAL/KYP/KYP_INTERFACE.h"
#include "HAL/SRVM/SRVM_INTERFACE.h"
#include "HAL/EX_EEPROM/EXEEPROM_INTERFACE.h"

/* Configurations */
#define EEPROM_DOOR_ADDRESS					0x20
#define EEPROM_DOOR_NOT_ACCESSED			0xFF
#define PASSWORD_SIZE						4
#define NUMBER_OF_TRIALS					3
#define MAX_TIME_FOR_ACTION					10


int main(void)
{
	u8 LOC_Press = KYP_NOT_PRESSED;
	u8 LOC_eeprom;
	u8 LOC_iter , LOC_trials = NUMBER_OF_TRIALS;
	u8 LOC_PassArr[PASSWORD_SIZE];
	
	//Initializations
	Port_Init();
	KYP_Init();
	LCD_Init();
	EXEEPROM_vInit();
	
	// Read the Address of password to check if it has been written before
	EXEEPROM_vReadByte(EEPROM_DOOR_ADDRESS,&LOC_eeprom);
	
	//Set the password if it is the first time accessing
	if(LOC_eeprom == EEPROM_DOOR_NOT_ACCESSED)
	{
		LCD_Send_XY(1,8,"Welcome");
		LCD_Send_XY(2,1,"Set Your Password:");
		LCD_Send_XY(3,1,"");
		for(LOC_iter = 0 ; LOC_iter<PASSWORD_SIZE ; LOC_iter++)
		{
			do{
				LOC_Press = KYP_u8GetPressedKey();
				_delay_ms(200);
			}while(!(LOC_Press>='0' && LOC_Press<='9'));
			LCD_SendData(LOC_Press);
			_delay_ms(500);
			LCD_Send_XY(3,LOC_iter+1,"*");
			//write the number in its location in EEPROM
			EXEEPROM_vWriteByte(EEPROM_DOOR_ADDRESS+LOC_iter,LOC_Press);
		}
		
		LCD_SendCMD(CLR_SCREEN);
		LCD_Send_XY(2,4,"Password Saved");
		LCD_Send_XY(3,5,"Successfully");
		_delay_ms(1000);
		LCD_SendCMD(CLR_SCREEN);
	}
	
	LOC_iter = 0;
	
	//loop that breaks if the number of trials is passed or the password is correct
	while(LOC_trials>0 && LOC_iter!=PASSWORD_SIZE)
	{
		LCD_Send_XY(1,6,"Door LOCKED");
		LCD_Send_XY(2,1,"Enter Password:");
		LCD_Send_XY(3,1,"");
		for(LOC_iter=0 ; LOC_iter<PASSWORD_SIZE ; LOC_iter++)
		{
			do{
				LOC_Press = KYP_u8GetPressedKey();
				_delay_ms(200);
			}while(!(LOC_Press>='0' && LOC_Press<='9'));
			LCD_SendData(LOC_Press);
			_delay_ms(500);
			LCD_Send_XY(3,LOC_iter+1,"*");
			//storing the entered password in an array
			LOC_PassArr[LOC_iter] = LOC_Press;
		}
		
		//for loop compares the stored password with the entered, LOC_iter = PASSWORD_SIZE if the password is correct
		for(LOC_iter=0 ; LOC_iter<PASSWORD_SIZE ; LOC_iter++)
		{
			EXEEPROM_vReadByte(EEPROM_DOOR_ADDRESS+LOC_iter,&LOC_eeprom);
			if(LOC_eeprom != LOC_PassArr[LOC_iter])
			{
				LOC_trials--;
				break;
			}
		}
		
		//the password is wrong
		if(LOC_iter != PASSWORD_SIZE)
		{
			LCD_SendCMD(CLR_SCREEN);
			LCD_Send_XY(1,3,"Wrong Password");
			LCD_Send_XY(3,1,"");
			LCD_SendData(LOC_trials+48);
			if(LOC_trials == 1 || LOC_trials == 0)
			{
				LCD_SendString(" Trial Left");
			}
			else
			{
				LCD_SendString(" Trials Left");
			}
			_delay_ms(1500);
			LCD_SendCMD(CLR_SCREEN);
		}
	}
	
	//last trial is also wrong
	if(LOC_trials == 0)
	{
		LCD_SendCMD(CLR_SCREEN);
		LCD_Send_XY(1,4,"Wrong Password");
		
		//looping forever on the alert
		while(1)
		{
			Dio_WriteChannel(PA_4,STD_HIGH);
			Dio_WriteChannel(PC_6,STD_HIGH);
			_delay_ms(500);
			Dio_WriteChannel(PA_4,STD_LOW);
			Dio_WriteChannel(PC_6,STD_LOW);
			_delay_ms(100);
		}
	}
	
	//the password is correct
	else
	{
		LCD_SendCMD(CLR_SCREEN);
		LCD_Send_XY(1,7,"Welcome");
		LCD_Send_XY(3,3,"Door UNLOCKED");
		//unlocking the door by rotating the servo 90
		SRVM_voidOn(90);
	}							
    while(1)
    {
        
    }
}