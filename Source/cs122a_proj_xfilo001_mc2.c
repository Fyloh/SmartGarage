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
#include "usart_ATmega1284.h"
#include "nokia5110.h"
#include "keypad.h"


// Flags & Variables from Usart
unsigned char U0_RxD;
unsigned char temp;
unsigned char IR_1, IR_2;
unsigned char BT;
unsigned char FSR;
unsigned char LD = 0x00;
unsigned char LD_BT_Flag;
unsigned char ACT;

// Keypad & Display Variables
unsigned char key;
unsigned char key_dec;
unsigned char keypad_flag = 0x00;
unsigned char keypad_curr_flag = 0x00;
unsigned char keypad_pass_flag = 0x00;
unsigned char keypad_correct = 0x00;
unsigned char menu_key;
unsigned char LD_STATE_FLAG = 0x00;

// Garage Flags
unsigned char IR_CLOSE_FLAG = 0x00;
unsigned char garage_status;

unsigned char keypad_key;
char temp_pass_arr[4] = {'X', 'X', 'X', 'X'};
char pass_arr[4] = {'1', '1', '1', '1'};

void nokia_decide_temp() {
	if(temp == 0) { nokia_lcd_write_string("FIRE", 1); }
	else if(temp == 1) { nokia_lcd_write_string("1", 1); }
	else if(temp == 2) { nokia_lcd_write_string("2", 1); }
	else if(temp == 3) { nokia_lcd_write_string("3", 1); }
	else if(temp == 4) { nokia_lcd_write_string("4", 1); }
	else if(temp == 5) { nokia_lcd_write_string("5", 1); }
	else if(temp == 6) { nokia_lcd_write_string("6", 1); }
	else if(temp == 7) { nokia_lcd_write_string("7", 1); }
	else if(temp == 8) { nokia_lcd_write_string("8", 1); }
	else if(temp == 9) { nokia_lcd_write_string("9", 1); }
	else if(temp == 10) { nokia_lcd_write_string("10", 1); }
	else if(temp == 11) { nokia_lcd_write_string("11", 1); }
	else if(temp == 12) { nokia_lcd_write_string("12", 1); }
	else if(temp == 13) { nokia_lcd_write_string("13", 1); }
	else if(temp == 14) { nokia_lcd_write_string("14", 1); }
	else if(temp == 15) { nokia_lcd_write_string("15", 1); }
	else if(temp == 16) { nokia_lcd_write_string("16", 1); }
	else if(temp == 17) { nokia_lcd_write_string("17", 1); }
	else if(temp == 18) { nokia_lcd_write_string("18", 1); }
	else if(temp == 19) { nokia_lcd_write_string("19", 1); }
	else if(temp == 20) { nokia_lcd_write_string("20", 1); }
	else if(temp == 21) { nokia_lcd_write_string("21", 1); }
	else if(temp == 22) { nokia_lcd_write_string("22", 1); }
	else if(temp == 23) { nokia_lcd_write_string("23", 1); }
	else if(temp == 24) { nokia_lcd_write_string("24", 1); }
	else if(temp == 25) { nokia_lcd_write_string("25", 1); }
	else if(temp == 26) { nokia_lcd_write_string("26", 1); }
	else if(temp == 27) { nokia_lcd_write_string("27", 1); }
	else if(temp == 28) { nokia_lcd_write_string("28", 1); }
	else if(temp == 29) { nokia_lcd_write_string("29", 1); }
	else if(temp == 30) { nokia_lcd_write_string("30", 1); }
	else if(temp == 31) { nokia_lcd_write_string("31", 1); }
	else if(temp == 32) { nokia_lcd_write_string("32", 1); }
	else if(temp == 33) { nokia_lcd_write_string("33", 1); }
	else if(temp == 34) { nokia_lcd_write_string("34", 1); }
	else if(temp == 35) { nokia_lcd_write_string("35", 1); }
	else if(temp == 36) { nokia_lcd_write_string("36", 1); }
	else if(temp == 37) { nokia_lcd_write_string("37", 1); }
	else if(temp == 38) { nokia_lcd_write_string("38", 1); }
	else if(temp == 39) { nokia_lcd_write_string("39", 1); }
	else if(temp == 40) { nokia_lcd_write_string("40", 1); }
	else if(temp == 41) { nokia_lcd_write_string("41", 1); }
	else if(temp == 42) { nokia_lcd_write_string("42", 1); }
	else if(temp == 43) { nokia_lcd_write_string("43", 1); }
	else if(temp == 44) { nokia_lcd_write_string("44", 1); }
	else if(temp == 45) { nokia_lcd_write_string("46", 1); }
	else if(temp == 46) { nokia_lcd_write_string("46", 1); }
	else if(temp == 47) { nokia_lcd_write_string("47", 1); }
	else if(temp == 48) { nokia_lcd_write_string("48", 1); }
	else if(temp == 49) { nokia_lcd_write_string("49", 1); }
	else if(temp == 50) { nokia_lcd_write_string("50", 1); }
	else if(temp == 51) { nokia_lcd_write_string("51", 1); }
	else if(temp == 52) { nokia_lcd_write_string("52", 1); }
	else if(temp == 53) { nokia_lcd_write_string("53", 1); }
	else if(temp == 54) { nokia_lcd_write_string("54", 1); }
	else if(temp == 55) { nokia_lcd_write_string("55", 1); }
	else if(temp == 56) { nokia_lcd_write_string("56", 1); }
	else if(temp == 57) { nokia_lcd_write_string("57", 1); }
	else if(temp == 58) { nokia_lcd_write_string("58", 1); }
	else if(temp == 59) { nokia_lcd_write_string("59", 1); }
	else if(temp == 60) { nokia_lcd_write_string("60", 1); }
	else if(temp == 61) { nokia_lcd_write_string("61", 1); }
	else if(temp == 62) { nokia_lcd_write_string("62", 1); }
	else if(temp == 63) { nokia_lcd_write_string("63", 1); }
	else if(temp == 64) { nokia_lcd_write_string("64", 1); }
	else if(temp == 65) { nokia_lcd_write_string("65", 1); }
	else if(temp == 66) { nokia_lcd_write_string("66", 1); }
	else if(temp == 67) { nokia_lcd_write_string("67", 1); }
	else if(temp == 68) { nokia_lcd_write_string("68", 1); }
	else if(temp == 69) { nokia_lcd_write_string("69", 1); }
	else if(temp == 70) { nokia_lcd_write_string("70", 1); }
	else if(temp == 71) { nokia_lcd_write_string("71", 1); }
	else if(temp == 72) { nokia_lcd_write_string("72", 1); }
	else if(temp == 73) { nokia_lcd_write_string("73", 1); }
	else if(temp == 74) { nokia_lcd_write_string("74", 1); }
	else if(temp == 75) { nokia_lcd_write_string("75", 1); }
	else if(temp == 76) { nokia_lcd_write_string("76", 1); }
	else if(temp == 77) { nokia_lcd_write_string("77", 1); }
	else if(temp == 78) { nokia_lcd_write_string("78", 1); }
	else if(temp == 79) { nokia_lcd_write_string("79", 1); }
	else if(temp == 80) { nokia_lcd_write_string("80", 1); }
	else if(temp == 81) { nokia_lcd_write_string("81", 1); }
	else if(temp == 82) { nokia_lcd_write_string("82", 1); }
	else if(temp == 83) { nokia_lcd_write_string("83", 1); }
	else { nokia_lcd_write_string("FIRE", 1); 
}

enum Receive_States {Receive_Init} Receive_State;

void Receive() {
	
	switch(Receive_State) {
		case Receive_Init:
				if(USART_HasReceived(0)) {
					U0_RxD = USART_Receive(0);
					// Flagged Data Sent
					if((U0_RxD & 0xC0) == 0xC0) {
						
						IR_1 = U0_RxD & 0x01;
						IR_2 = (U0_RxD & 0x02) >> 1;
						FSR = (U0_RxD & 0x04) >> 2;
						BT = (U0_RxD & 0x38) >> 3;
						
						if ((BT & 0x03) == 0x03) {
							ACT = 0x00;
						}
						
						else if((BT & 0x01) == 0x01) {
							ACT = 0x01;
						}
						
						
						if((BT & 0x07) == 0x07) {
							if(LD_BT_Flag != 0x01) {
								LD = 0x01;
								LD_BT_Flag = 0x01;
							}
							
							else {
								LD = LD;
							}
						}
						
						else {
							LD_BT_Flag = 0x00;
						}
						
						if(garage_status == 0x10 && IR_1) {
							IR_CLOSE_FLAG = 0x01;
						}
						
						
						
					}
					// Temperature Data Sent
					else if((U0_RxD & 0xC0) == 0x00) {
						temp = U0_RxD;
					}
				}
				break;
			
		default:
			break;
	}
	
}

void Receive_Task() {
	Receive_State = Receive_Init;
	while(1) {
		Receive();
		vTaskDelay(10);
	}
}

enum Motor_States {Motor_Init, Motor_Closed, Motor_Opened, Motor_Close, Motor_Open} Motor_State;

int motor_cnt = 0;
unsigned char array[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};

void Motor() {
	
	switch(Motor_State) {
		case Motor_Init:
			Motor_State = Motor_Closed;
			break;
		
		case Motor_Closed:
			if(ACT && !LD)
				Motor_State = Motor_Open;
			else if(!ACT || LD)
				Motor_State = Motor_Closed;
			break;
		
		case Motor_Open:
			if((!ACT || LD) && !IR_CLOSE_FLAG)
				Motor_State = Motor_Close;
			else if(motor_cnt > 4096)
				Motor_State = Motor_Opened;
			break;
		
		case Motor_Close:
			
			if((ACT || IR_1) && !LD)
				Motor_State = Motor_Open;
			else if(motor_cnt < 0)
				Motor_State = Motor_Closed;
			break;
		
		case Motor_Opened:
			if(!ACT || LD)
				Motor_State = Motor_Close;
			else if(ACT && !LD)
				Motor_State = Motor_Opened;
			break;
		
		default:
			break;
	}
	
	switch(Motor_State){
		case Motor_Closed:
			garage_status = 0x00;
			motor_cnt = 0;
			break;
		
		case Motor_Open:
			garage_status = 0x01;
			++motor_cnt;
			PORTB = (array[motor_cnt % 8] | (array[motor_cnt % 8] << 4));
			break;
		
		case Motor_Close:
			garage_status = 0x10;
			--motor_cnt;
			PORTB = (array[motor_cnt % 8] | (array[motor_cnt % 8] << 4));
			break;
		
		case Motor_Opened:
			IR_CLOSE_FLAG = 0x00;
			garage_status = 0x11;
			motor_cnt = 4096;
				
			break;
		
		default:
			break;
	}
}

void Motor_Task() {
	Motor_State = Motor_Init;
	while(1) {
		Motor();
		vTaskDelay(3);
	}
}


enum Menu_States {Menu_Init, Menu_Main, Menu_Status, Menu_S2M, Menu_Pass, Menu_P2M, Menu_Change, Menu_Wrong, Menu_Lockdown, Menu_LD2M} Menu_State;

void Menu() {
	key = GetKeypadKey();
	key_dec = key - 48;
	
	switch(Menu_State) {
		case Menu_Init:
			nokia_lcd_clear();
			nokia_lcd_write_string("Welcome to Smart Garage",1);
			nokia_lcd_render();
			delay_ms(4000);
			
			Menu_State = Menu_Main;
			break;
		
		case Menu_Main:
			
			if(key != 'A' && key != 'B' && key != 'C') {
				Menu_State = Menu_Main; }
			else if(key == 'A') {
				Menu_State = Menu_Status;
				menu_key = 0x01; }
			else if(key == 'B') {
				Menu_State = Menu_Pass;
				menu_key = 0x02; }
			else if(key == 'C') {
				Menu_State = Menu_Pass;
				menu_key = 0x03; }
			
			break;
			
		// Hit 'B' To GoTo Main Menu
		case Menu_Status:
			
			if(key != 'B') {
				Menu_State = Menu_Status; }
			else if(key == 'B') {
				Menu_State = Menu_S2M; }
				
			break;
		
		// Wait for 'B' to become released
		case Menu_S2M:
			
			if(key_dec >= 0 && key_dec <= 9) {
				Menu_State = Menu_S2M; }
			else if(key == '\0') {
				Menu_State = Menu_Main; }
			else {
				Menu_State = Menu_S2M; }
				
			break;
			
		case Menu_Pass:
			// Correct
			if(keypad_correct == 0xFF && keypad_flag == 0x00) {
				keypad_correct = 0x00;
				keypad_curr_flag = 0x00;
				
				// If we wanted to go to lockdown, then lockdown
				if(menu_key == 0x03) {
					Menu_State = Menu_Lockdown;
					menu_key = 0x00;
				}
				
				else {
					Menu_State = Menu_Change;
				}
			}
			
			// Wrong
			else if(keypad_correct == 0x0F && keypad_flag == 0x00) {
				keypad_correct = 0x00;
				keypad_curr_flag = 0x00;
				Menu_State = Menu_Wrong;
			}
			
			else if(key != 'A') {
				Menu_State = Menu_Pass; }
			else if(key == 'A') {
				/* RESET APPROPRIATE FLAGS */
				keypad_flag = 0x00;
				keypad_curr_flag = 0x00;
				/* RESET APPROPRIATE FLAGS */
				Menu_State = Menu_P2M; }
				
			break;
		
		// Wait for 'A' to become released
		case Menu_P2M:
			if(key_dec >= 0 && key_dec <= 9) {
				Menu_State = Menu_P2M; }
			else if(key == '\0') {
				Menu_State = Menu_Main; }
			else {
				Menu_State = Menu_P2M; }
				
			break;
			
		case Menu_Wrong:
			vTaskDelay(1000);
			Menu_State = Menu_Main;
			break;
		
		case Menu_Change:
			if(keypad_flag == 0x00) {
				Menu_State = Menu_Main;
			}
			
			else if(key != 'A') {
				Menu_State = Menu_Change; }
			else if(key == 'A') {
				/* RESET APPROPRIATE FLAGS */
				keypad_flag = 0x00;
				keypad_pass_flag = 0x00;
				/* RESET APPROPRIATE FLAGS */
				Menu_State = Menu_P2M; 
			}
			
			break;
			
		case Menu_Lockdown:
			if(key == 'B') {
				LD_STATE_FLAG = 0x00;
				Menu_State = Menu_LD2M;
			}
			else {
				Menu_State = Menu_Lockdown;
			}
			break;
			
		case Menu_LD2M:
			if(key_dec >= 0 && key_dec <= 9) {
				Menu_State = Menu_LD2M; }
			else if(key == '\0') {
				Menu_State = Menu_Main;
			}
			else {
				Menu_State = Menu_LD2M; }
			break;
			
			
		default:
			break;
	}
	
	switch(Menu_State) {
		case Menu_Init:
			break;
			
		case Menu_Main:
			nokia_lcd_clear();
			nokia_lcd_write_string("Main Menu:", 1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_string("View Status: A", 1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_string("Change Pass: B", 1);
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_string("Lockdown: C", 1);
			nokia_lcd_set_cursor(0, 32);
			nokia_lcd_write_char(eeprom_read_byte(0) + 48, 1);
			nokia_lcd_write_char(eeprom_read_byte(1) + 48, 1);
			nokia_lcd_write_char(eeprom_read_byte(2) + 48, 1);
			nokia_lcd_write_char(eeprom_read_byte(3) + 48, 1);
			nokia_lcd_render();
			break;
		
		case Menu_Status:
			nokia_lcd_clear();
			
			nokia_lcd_write_string("~~Status~~", 1);
			nokia_lcd_set_cursor(0, 8);
			
			nokia_lcd_write_string("G: ", 1);
			if(garage_status == 0x00) {
				nokia_lcd_write_string("Closed", 1);
			}
			else if(garage_status == 0x01) {
				nokia_lcd_write_string("Opening", 1);
			}
			else if(garage_status == 0x10) {
				nokia_lcd_write_string("Closing", 1);
			}
			else if(garage_status == 0x11) {
				nokia_lcd_write_string("Opened", 1);
			}
			nokia_lcd_set_cursor(0, 16);
			// If IR2 Detects Someone Outside
			nokia_lcd_write_string("Outside: ", 1);
			if(IR_2 && garage_status == 0x11)
				nokia_lcd_write_string("Yes", 1);
			else
				nokia_lcd_write_string("No", 1);
			nokia_lcd_set_cursor(0, 24);
			nokia_lcd_write_string("Temp: ", 1);
			// Function above writes to Nokia
			nokia_decide_temp();
			nokia_lcd_set_cursor(0, 32);
			nokia_lcd_write_string("Lockdown: ", 1);
			if(LD == 0x01) { nokia_lcd_write_string("Yes", 1);}
			else if(LD == 0x00) {nokia_lcd_write_string("No", 1);}
			nokia_lcd_set_cursor(0, 40);
			nokia_lcd_write_string("Car In: ", 1);
			if(FSR) {
				nokia_lcd_write_string("Yes", 1);
			}
			else {
				nokia_lcd_write_string("No", 1);
			}
			nokia_lcd_render();
			break;
			
		case Menu_S2M:
			nokia_lcd_clear();
			nokia_lcd_write_string("Release Btns", 2);
			nokia_lcd_render();
			break;
			
		case Menu_Pass:
			/* SET APPROPRIATE FLAGS */
			keypad_flag = 0x01;
			keypad_curr_flag = 0x01;
			/* SET APPROPRIATE FLAGS */
			
			nokia_lcd_clear();
			nokia_lcd_write_string("~~Enter Pass~~", 1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_string("Curr Pass: ", 1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_char(temp_pass_arr[0], 1);
			nokia_lcd_write_char(temp_pass_arr[1], 1);
			nokia_lcd_write_char(temp_pass_arr[2], 1);
			nokia_lcd_write_char(temp_pass_arr[3], 1);
			nokia_lcd_render();
			
			break;
			
		case Menu_P2M:
			nokia_lcd_clear();
			nokia_lcd_write_string("Release Btns", 2);
			nokia_lcd_render();
			break;
			
		case Menu_Wrong:
			nokia_lcd_clear();
			nokia_lcd_write_string("WRONG", 2);
			nokia_lcd_render();
			break;
			
		case Menu_Change:
			/* SET APPROPRIATE FLAGS */
			keypad_flag = 0x01;
			keypad_pass_flag = 0x01;
			/* SET APPROPRIATE FLAGS */
			
			nokia_lcd_clear();
			nokia_lcd_write_string("~~Change Pass~~", 1);
			nokia_lcd_set_cursor(0, 8);
			nokia_lcd_write_string("New Pass: ", 1);
			nokia_lcd_set_cursor(0, 16);
			nokia_lcd_write_char(temp_pass_arr[0], 1);
			nokia_lcd_write_char(temp_pass_arr[1], 1);
			nokia_lcd_write_char(temp_pass_arr[2], 1);
			nokia_lcd_write_char(temp_pass_arr[3], 1);
			nokia_lcd_render();
			break;
			
		case Menu_LD2M:
			nokia_lcd_clear();
			nokia_lcd_write_string("Release Btns", 2);
			nokia_lcd_render();
			break;
		
		case Menu_Lockdown:
			nokia_lcd_clear();
			if(LD_STATE_FLAG == 0x00) {
				if(LD == 0x00) {
					nokia_lcd_write_string("Was: Inactive", 1);
					nokia_lcd_set_cursor(0, 8);
					nokia_lcd_write_string("Now: Active ", 1);
					LD = 0x01;
				}
				
				else if(LD == 0x01) {
					nokia_lcd_write_string("Was: Active", 1);
					nokia_lcd_set_cursor(0, 8);
					nokia_lcd_write_string("Now: Inactive ", 1);
					LD = 0x00;
				}
				
				LD_STATE_FLAG = 0x01;
			}
			
			if(LD == 0x01) {
				nokia_lcd_write_string("Was: Inactive", 1);
				nokia_lcd_set_cursor(0, 8);
				nokia_lcd_write_string("Now: Active ", 1);
			}
			
			else if(LD == 0x00) {
				nokia_lcd_write_string("Was: Active", 1);
				nokia_lcd_set_cursor(0, 8);
				nokia_lcd_write_string("Now: Inactive ", 1);
			}
			
			nokia_lcd_render();
			break;
			
		default:
			break;
			
	}
}
	
void Menu_Task() {
	Menu_State = Menu_Init;
	while(1) {
		Menu();
		vTaskDelay(1);
	}
}

enum KP_States {KP_Init, KP_Poll_1, KP_Mid_1_2, KP_Poll_2, KP_Mid_2_3, KP_Poll_3, KP_Mid_3_4, KP_Poll_4, KP_Mid_4_Init} KP_State;

void Keypad() {
	// Grab Keypad Input
	keypad_key = GetKeypadKey();
	
	switch(KP_State) {
		case KP_Init:
			// If Flag is set from the menu
			temp_pass_arr[0] = 'X';
			temp_pass_arr[1] = 'X';
			temp_pass_arr[2] = 'X';
			temp_pass_arr[3] = 'X';
			
			if(keypad_flag == 0x01)
				KP_State = KP_Poll_1;
				
			break;
		
		case KP_Poll_1:
			// If Flag is sent from the menu, means 'A' was hit so stop taking input
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// If Keypad input is not empty and it is a number then, fill temporary password array
			else if(keypad_key != '\0' && (keypad_key - 48) >= 0 && (keypad_key - 48) <= 9) {
				temp_pass_arr[0] = keypad_key;
				KP_State = KP_Mid_1_2;
			}
			
			break;
			
		case KP_Mid_1_2:
			// If Flag is sent from the menu, means 'A' was hit so stop taking input
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// If the button is released, continue
			// Else stay in the same state waiting for the button to be released
			else if(keypad_key == '\0')
				KP_State = KP_Poll_2;
			else
				KP_State = KP_Mid_1_2;
			
			break;
		
		case KP_Poll_2:
			// Similar Comments Above
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// Similar Comments Above
			else if(keypad_key != '\0' && (keypad_key - 48) >= 0 && (keypad_key - 48) <= 9) {
				temp_pass_arr[1] = keypad_key;
				KP_State = KP_Mid_2_3;
			}
			
			break;
			
		case KP_Mid_2_3:
			// Similar Comments Above
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// Similar Comments Above
			else if(keypad_key == '\0')
				KP_State = KP_Poll_3;
			else
				KP_State = KP_Mid_2_3;
			
			break;
		
		case KP_Poll_3:
			// Similar Comments Above
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// Similar Comments Above
			else if(keypad_key != '\0' && (keypad_key - 48) >= 0 && (keypad_key - 48) <= 9) {
				temp_pass_arr[2] = keypad_key;
				KP_State = KP_Mid_3_4;
			}
			
			break;
			
		case KP_Mid_3_4:
			// Similar Comments Above
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// Similar Comments Above
			else if(keypad_key == '\0')
				KP_State = KP_Poll_4;
			else
				KP_State = KP_Mid_3_4;
			
			break;
		
		case KP_Poll_4:
			// If Flag is sent from the menu, that means 'A' was hit so stop taking input
			if(keypad_flag == 0x00) {
				KP_State = KP_Init;
			}
			
			// If Keypad input is not empty and its a number then, use the last input and then 
			else if(keypad_key != '\0' && (keypad_key - 48) >= 0 && (keypad_key - 48) <= 9) {
				temp_pass_arr[3] = keypad_key;
				KP_State = KP_Mid_4_Init;
				
				
				// check if we are checking for the current password
				if(keypad_curr_flag == 0x01) {
					pass_arr[0] = eeprom_read_byte(0) + 48;
					pass_arr[1] = eeprom_read_byte(1) + 48;
					pass_arr[2] = eeprom_read_byte(2) + 48;
					pass_arr[3] = eeprom_read_byte(3) + 48;
					// if the password is correct to the current password
					if (temp_pass_arr[0] == pass_arr[0] && temp_pass_arr[1] == pass_arr[1] && temp_pass_arr[2] == pass_arr[2] && temp_pass_arr[3] == pass_arr[3]) {
						// Correct
						keypad_correct = 0xFF;
					}
					
					// else its wrong and send out a wrong flag
					else {
						// Wrong
						keypad_correct = 0x0F;
					}
					
					// reset this flag since we are done taking in bits
					keypad_curr_flag = 0x00;
					
				}
				
				// If we are changing the password
				else if(keypad_pass_flag == 0x01) {
					eeprom_write_byte(0, temp_pass_arr[0] - 48);
					eeprom_write_byte(1, temp_pass_arr[1] - 48);
					eeprom_write_byte(2, temp_pass_arr[2] - 48);
					eeprom_write_byte(3, temp_pass_arr[3] - 48);
					
					keypad_pass_flag = 0x00;
				}
			}
			
			break;
			
		case KP_Mid_4_Init:
			// Go back to Init if we let go of last button or flag is sent from Menu
			if(keypad_key == '\0' || keypad_flag == 0x00) {
				// Set flag down to let Menu SM know we are done polling
				keypad_flag = 0x00;
				KP_State = KP_Init;
			}
			
			// Else stay waiting for last button to be released
			else {
				KP_State = KP_Mid_4_Init;
			}
			
			break;
			
		default:
			break;
	}
	
	
}

void Keypad_Task() {
	KP_State = KP_Init;
	while(1) {
		Keypad();
		vTaskDelay(1);
	}
}

int main(void) {
	
	// initialize ports
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	
	// Initialize USART
	initUSART(0);
	
	// Power Nokia Screen
	nokia_lcd_power(1);
	nokia_lcd_init();
	
	xTaskCreate(Motor_Task, (signed portCHAR *)"Motor_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(Menu_Task, (signed portCHAR *)"Menu_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(Receive_Task, (signed portCHAR *)"Receive_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
	xTaskCreate(Keypad_Task, (signed portCHAR *)"Keypad_Task", configMINIMAL_STACK_SIZE, NULL, 1, NULL );
    vTaskStartScheduler(); 
	
}
