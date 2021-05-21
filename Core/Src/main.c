/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stdlib.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "kb.h"
#include "sdk_uart.h"
#include "pca9538.h"
#include "oled.h"
#include "fonts.h"
#include <stdio.h>
#include <string.h>
#include "tim.h"
#include "buzzer.h"

#define Xcoor -3
#define Ycoor -2


//I2C_HandleTypeDef hi2c1;

//TIM_HandleTypeDef htim2;

//UART_HandleTypeDef huart6;


void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_I2C1_Init(void);
//static void MX_TIM2_Init(void);
//static void MX_USART6_UART_Init(void);

int t =0;
int control = 0;
uint16_t OLED_Keys[12] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30};
uint16_t A[100] ;

void KB_Test( void );
void OLED_KB( uint16_t OLED_Keys[]);

void oled_Reset( void );
//void print_timer(uint8_t A[]);
void print_timer(uint16_t , uint16_t , uint16_t , uint8_t , uint16_t);

uint16_t hours, minutes, seconds, count;
uint16_t timer_val;


int main(void)
{

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART6_UART_Init();

  MX_TIM2_Init();
 // HAL_TIM_Base_Start(&htim2);

  MX_TIM3_Init();
  HAL_TIM_Base_Start(&htim3);

  oled_Init();
  Buzzer_Init();


  uint32_t megalovania_melody[] = {
  			N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_C3, N_C3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_B2, N_B2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_AS2, N_AS2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_D3, N_D3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_C3, N_C3, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_B2, N_B2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_AS2, N_AS2, N_D4, N_A3, 0, N_GS3, N_G3, N_F3, N_D3, N_F3, N_G3, N_D4, N_D4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_C4, N_C4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_B3, N_B3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_AS3, N_AS3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_D4, N_D4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_C4, N_C4, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_B3, N_B3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_AS3, N_AS3, N_D5, N_A4, 0, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, N_F4, N_F4, N_F4, N_F4, N_F4, N_D4, N_D4, N_D4, N_F4, N_F4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_G4, 0, N_F4, N_F4, N_F4, N_G4, N_GS4, N_A4, N_C5, N_A4, N_D5, N_D5, N_D5, N_A4, N_D5, N_C5, N_F4, N_F4, N_F4, N_F4, N_F4, N_D4, N_D4, N_D4, N_F4, N_F4, N_F4, N_F4, N_D4, N_F4, N_E4, N_D4, N_C4, 0, N_G4, N_E4, N_D4, N_D4, N_D4, N_D4, N_F3, N_G3, N_AS3, N_C4, N_D4, N_F4, N_C5, 0, N_F4, N_D4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_F4, N_F4, N_GS4, N_A4, N_C5, N_A4, N_GS4, N_G4, N_F4, N_D4, N_E4, N_F4, N_G4, N_A4, N_C5, N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4, N_F3, N_G3, N_A3, N_F4, N_E4, N_D4, N_E4, N_F4, N_G4, N_E4, N_A4, N_A4, N_G4, N_F4, N_DS4, N_CS4, N_DS4, 0, N_F4, N_D4, N_F4, N_G4, N_GS4, N_G4, N_F4, N_D4, N_GS4, N_G4, N_F4, N_D4, N_F4, N_F4, N_F4, N_GS4, N_A4, N_C5, N_A4, N_GS4, N_G4, N_F4, N_D4, N_E4, N_F4, N_G4, N_A4, N_C5, N_CS5, N_GS4, N_GS4, N_G4, N_F4, N_G4, N_F3, N_G3, N_A3, N_F4, N_E4, N_D4, N_E4, N_F4, N_G4, N_E4, N_A4, N_A4, N_G4, N_F4, N_DS4, N_CS4, N_DS4,
  	};
  	uint32_t megalovania_delays[] = {
  			16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 16, 16, 8, 6, 32, 8, 8, 8, 16, 16, 16, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 16, 16, 16, 16, 16, 8, 8, 16, 8, 8, 8, 8, 8, 8, 8, 8, 16, 16, 16, 2, 8, 16, 8, 8, 8, 8, 4, 16, 8, 16, 8, 8, 8, 8, 8, 16, 8, 16, 8, 8, 8, 8, 8, 8, 8, 16, 8, 15, 8, 8, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 2, 16, 8, 16, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8,  8, 8, 16, 16, 16, 2, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 8, 2, 2, 3, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 2, 16, 8, 16, 8, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8,  8, 8, 16, 16, 16, 2, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 2, 8, 8, 8, 8, 2, 1
  	};
  	uint32_t zelda_melody[] = {
  			N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, 0, N_GS4, N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, 0, N_GS4, N_AS4, 0, 0, N_AS4, N_AS4, N_AS4, N_AS4, N_AS4, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_AS5, N_AS5, N_AS5, N_GS5, N_FS5, N_GS5, 0, N_FS5, N_F5, N_F5, N_DS5, N_DS5, N_F5, N_FS5, N_F5, N_DS5, N_CS5, N_CS5, N_DS5, N_F5, N_DS5, N_CS5, N_C5, N_C5, N_D5, N_E5, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_CS6, N_C6, N_A5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_D5, N_DS5, 0, N_FS5, N_F5, N_CS5, 0, N_AS4, N_C5, N_C5, N_D5, N_E5, 0, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_AS5, N_AS5, N_AS5, N_GS5, N_FS5, N_GS5, 0, N_FS5, N_F5, N_F5, N_DS5, N_DS5, N_F5, N_FS5, N_F5, N_DS5, N_CS5, N_CS5, N_DS5, N_F5, N_DS5, N_CS5, N_C5, N_C5, N_D5, N_E5, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_AS4, N_F3, N_F3, 0, N_AS4, N_AS4, N_C5, N_D5, N_DS5, N_F5, 0, N_F5, N_F5, N_FS5, N_GS5, N_AS5, 0, N_CS6, N_C6, N_A5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_F5, N_FS5, 0, N_AS5, N_A5, N_F5, 0, N_D5, N_DS5, 0, N_FS5, N_F5, N_CS5, 0, N_AS4, N_C5, N_C5, N_D5, N_E5, 0, N_G5, N_F5, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3, N_F3
  	};
  	uint32_t zelda_delays[] = {
  			2, 8, 8, 8, 8, 8, 8, 6, 16, 16, 4, 8, 8, 8, 8, 8, 8, 6, 16, 16, 4, 8, 8, 8, 8, 8, 8, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 8, 8, 8 ,8 ,8, 8, 6, 16, 16, 2, 4, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 8, 8, 8 ,8 ,8, 8, 6, 16, 16, 2, 4, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 8, 8, 8, 16, 16, 2, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8, 4, 4, 6, 16, 16, 16, 16, 16, 16, 2, 8, 8, 8 ,8 ,8, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 8, 16, 16, 4, 4, 4, 8, 16, 16, 8, 16, 16, 8, 16, 16, 8, 8
  	};

  while(1)
    {

	 hours = (A[0]-48)*10+(A[1]-48)*1;
  	 minutes = (A[3]-48)*10 + (A[4]-48)*1;
  	 seconds = (A[6]-48)*10+ (A[7]-48)*1;
     count = seconds + minutes *60 + hours *3600;

       oled_SetCursor(0,0);
       oled_WriteString("Time setting: ",Font_7x10,White);
      	  KB_Test();

      	 HAL_Delay(95);
      	 if(A[8] == '<' )
      	 {
      		// control = 8;
      		 break;
      	 }

    }

 	  while( __HAL_TIM_GET_COUNTER(&htim3) - timer_val >= 385 && count >0)
 	  	  	 	 {

 		  	  	  char str[20], hour[20], minute[20], second[20];
 	  	  	 		  hours = count / 3600;
 	  	  	 		  minutes = (count - 3600 *hours)/60;
 	  	  	 		  seconds = count - hours*3600 - minutes*60;

 	  	  	 			  	sprintf(str, "%d", count);
 	  	  	 			    sprintf(hour, "%d", hours);
 	  	  	 			    sprintf(minute, "%d", minutes);
 	  	  	 			    sprintf(second, "%d", seconds);
 	  	  	 			    if(seconds < 10)
 	  	  	 				  {
 	  	  	 			    	char temp[20];
 	  	  	 			    	strcpy(temp,second);
 	  	  	 			    	second[0]=48;
 	  	  	 			    	second[1]='\0';
 	  	  	 			    	strcat(second,temp);
 	  	  	 				  }
 	  	  	 			    if(minutes < 10)
 	  	  	 				  {
 	  	  	 			    	char temp[20];
 	  	  	 			    	strcpy(temp,minute);
 	  	  	 			    	minute[0]=48;
 	  	  	 			    	minute[1]='\0';
 	  	  	 			    	strcat(minute,temp);
 	  	  	 				  }
 	  	  	 			    if(hours < 10)
 	  	  	 				  {
 	  	  	 			    	char temp[20];
 	  	  	 			    	strcpy(temp,hour);
 	  	  	 			    	hour[0]=48;
 	  	  	 			    	hour[1]='\0';
 	  	  	 			    	strcat(hour,temp);
 	  	  	 				  }

 	  	  	 			    oled_SetCursor(30+Xcoor,32+Ycoor);
 	  	  	 			    oled_WriteString(hour, Font_11x18, White);
 	  	  	 			    oled_WriteChar(':', Font_11x18, White);

 	  	  	 			    oled_SetCursor(60+Xcoor,32+Ycoor);
 	  	  	 			    oled_WriteString(minute, Font_11x18, White);
 	  	  	 			    oled_WriteChar(':', Font_11x18, White);

 	  	  	 			    oled_SetCursor(90+Xcoor,32+Ycoor);
 	  	  	 			    oled_WriteString(second, Font_11x18, White);
 	  	  	 			    timer_val = __HAL_TIM_GET_COUNTER(&htim3);
 	  	  	 			    count--;

 	  	  	 			    if(count  <= -1)
	  	  	 			    		break;

 	  	  	 			    else
 	  	  	 			    {
 	  	  	 			    	oled_UpdateScreen();
 	  	  	 			    	HAL_Delay(1000);
 	  	  	 			    }

	  	 	 }


	while(1)
	{
		  oled_UpdateScreen();
		  oled_SetCursor(90+Xcoor,32+Ycoor);
		  oled_WriteString("00", Font_11x18, White);
		  oled_UpdateScreen();
		  HAL_Delay(944);

		  Buzzer_Play(zelda_melody, zelda_delays, sizeof(zelda_melody) / sizeof(uint32_t));
		  HAL_Delay(1000);
		  Buzzer_Play(megalovania_melody, megalovania_delays, sizeof(megalovania_melody) / sizeof(uint32_t));
		  HAL_Delay(1000);
	}
}

void KB_Test( void ) {
	UART_Transmit( (uint8_t*)"KB test start\n" );
	uint8_t R = 0, C = 0, L = 0, Row[4] = {0x1E,0x3D, 0x7B, 0xF7}, Key, OldKey;
	//uint8_t Row[4] = {0xF7, 0x7B, 0x3D, 0x1E};
	//oled_Reset();

	//oled_WriteString("Time setting:", Font_7x10, White);
	OLED_KB(OLED_Keys);
	//oled_UpdateScreen();
	for ( int i = 0; i < 4; i++ ) {
		//while( !( R && C && L ) ) {
			OldKey = Key;
			Key = Check_Row(Row[i]);
			if ( Key == 0x01 ) {
				//UART_Transmit( (uint8_t*)"Right pressed\n" );
				R = 1;
				OLED_Keys[2+3*i] = 2+3*i+49;
				A[t++] = 2+3*i+49;
				oled_SetCursor(t*8-2,12);
				oled_WriteChar(A[t-1], Font_7x10, White);

				//OLED_KB(OLED_Keys);
			} else if ( Key == 0x02 ) {
				//UART_Transmit( (uint8_t*)"Center pressed\n" );
				C = 1;
				//OLED_Keys[1+3*i] = 1+3*i+49;
				if(i == 3)
					{
						OLED_Keys[1+3*i] = 48;
						A[t++] = 48;
						oled_SetCursor(t*8-2,12);
						oled_WriteChar(A[t-1], Font_7x10, White);
					}
				else{
					A[t++] = 1+3*i+49;
					oled_SetCursor(t*8-2,12);
					oled_WriteChar(A[t-1], Font_7x10, White);
				}
				//OLED_KB(OLED_Keys);

			} else if ( Key == 0x04 ) {
				//UART_Transmit( (uint8_t*)"Left pressed\n" );
				L = 1;
				OLED_Keys[3*i] = 3*i+49;
				A[t++] = 3*i+49;
				oled_SetCursor(t*8-2,12);
				oled_WriteChar(A[t-1], Font_7x10, White);
				//OLED_KB(OLED_Keys);
			}
		//}
		//R = C = L = 0;
		//HAL_Delay(25);
	}
	//UART_Transmit( (uint8_t*)"KB test complete\n");
}
void OLED_KB( uint16_t OLED_Keys[12]) {
	for (int i = 3; i >= 0; i--) {
		//oled_SetCursor(56, 5+(4-i)*10);
		for (int j = 0; j < 3; j++) {
			//oled_WriteChar(OLED_Keys[j+3*i], Font_7x10, White);
		}
	}
	oled_UpdateScreen();
}

void oled_Reset( void ) {
	oled_Fill(Black);
	oled_SetCursor(0, 0);
	oled_UpdateScreen();
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
