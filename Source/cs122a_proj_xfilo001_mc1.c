/* 
* CS122A Project - Smart Garage
* Name & Email: Xhoni Filo / xfilo001@ucr.edu
* Lab Section: 22
*
* I acknowledge all content contained herein, excluding functions referencing
* the nokia5110.h file, the nokia5110.h file itself, and template code, is my own original work.
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>

//FreeRTOS include files
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

// External files
#include "bit.h"
#include "lcd.h"
#include "keypad.h"
#include "usart_ATmega1284.h"
#include "nokia5110.h"


/* ***************** VARIABLES ******************** */
unsigned char IR_1, IR_2;
unsigned char FSR;
unsigned long ADC_temp, ADC_sens, ADC_temp;
unsigned char BT = 0x00;
unsigned char usart1_data;

//  ******************** ADC CODE ***************************
void A2D_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: Enables analog-to-digital conversion
	// ADSC: Starts analog-to-digital conversion
	// ADATE: Enables auto-triggering, allowing for constant
	//	    analog to digital conversions.
}

void Set_A2D_Pin(unsigned char pinNum) {
	ADMUX = (pinNum <= 0x07) ? pinNum : ADMUX;
	// Allow channel to stabilize
	static unsigned char i = 0;
	for ( i=0; i<15; i++ ) { asm("nop"); }
}
//  ********************** END CODE **************************


enum Poll_States {Poll_Init, Poll_IR, Poll_BT, Poll_ADC} Poll_State;
void Poll() {
	switch(Poll_State) {
		case Poll_Init:
			Poll_State = Poll_IR;	
			break;
		
		case Poll_IR:	
			IR_1 = !(PINA & 0x04);
			IR_2 = !(PINA & 0x08);
			
			Poll_State = Poll_BT;
			break;
			
		case Poll_BT:
			if(USART_HasReceived(0))
				BT = USART_Receive(0);
			
			Poll_State = Poll_ADC;
			break;
			
		case Poll_ADC:
			Set_A2D_Pin(0);
			ADC_temp = ADC * (5000/1024);
			ADC_temp = ((ADC_temp - 500) / 10);
			Set_A2D_Pin(1);
			
			Set_A2D_Pin(1);
			ADC_sens = ADC * (5000/1024);
			ADC_sens = (ADC_sens) / 1024;
			Set_A2D_Pin(0);
			
			// If the Force Resisting Sensor is greater than 2, which means there
			// is a car in the way then send out a signal
			if(ADC_sens > 2)
				FSR = 0x01;
			else
				FSR = 0x00;
			
			Poll_State = Poll_IR;
			break;
			
		default:
			break;
	}
	
	// Send Polled Data over USART1
	// 0xC
	if(USART_IsSendReady(1)) {
		usart1_data = (IR_1 | (IR_2 << 1) | (FSR << 2) | (BT << 3) | 0xC0);
		PORTC = usart1_data;
		USART_Send(usart1_data, 1);
		USART_Send(ADC_temp, 1);
	}
	
}

void Poll_Task() {
	Poll_State = Poll_Init;
	while(1) {
		Poll();
		vTaskDelay(1);
	}
}


int main(void) {
	
	// initialize ports
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	// Initialize ADC
	A2D_init();
	
	
	// Initialize USART
	initUSART(0);
	initUSART(1);
	
	
	xTaskCreate(Poll_Task, (signed portCHAR *)"Poll_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    vTaskStartScheduler(); 
	
}
