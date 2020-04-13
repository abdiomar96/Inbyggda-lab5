/*
 * lab5.c
 *
 * Labb5.c file contains code where the main program
 * is using a state machine following the Moores principle. Components 
 * used for this to achieve the information is a Temperature sensor, Arduino Leonardo and
 * Hitachi LCD display 
 *
 * Created: 2020-01-13 17:33:22
 * Author : Henrik Goth & Abdirahman Omar Ali
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "hmi/hmi.h"
#include "numkey/numkey.h"
#include "temp/temp.h"
#include "lcd/lcd.h"
#include "delay/delay.h"

char temp_str[17];
char *p_str1 = "Temperature:  ";

enum state{

	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF
	
};

typedef enum state state_t;



int main(void)
{	
	// initialize HMI (LCD and numeric keyboard)
	hmi_init();
	
	//Initialize the ADC and ISR.
	temp_init();
	
	
	

	uint8_t key;
	key =  numkey_read();
	
	enum state CURRENT_STATE = SHOW_TEMP_C;
	enum state NEXT_STATE;
	
	//sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
	//output_msg(p_str1, temp_str, 0);
	




	
    /* State Machine for the different modes when pressing keys 1,2, or 3 */
    while (1) 
    {
		switch(CURRENT_STATE){
			//First state
			case SHOW_TEMP_C:
			sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
			
			output_msg(p_str1, temp_str, 0);
			if (numkey_read()== NO_KEY || numkey_read() == '1'){
				NEXT_STATE = SHOW_TEMP_C;
				
			} if (numkey_read()== '2'){
				NEXT_STATE = SHOW_TEMP_F;
				
			}  if (numkey_read() == '3'){
				NEXT_STATE = SHOW_TEMP_CF;
			}
			CURRENT_STATE = NEXT_STATE;
			break;
			{
				case SHOW_TEMP_F:
				sprintf(temp_str, "%u%cF", temp_read_fahrenheit(), 0xDF);
				output_msg(p_str1, temp_str, 0);
			if (numkey_read()== NO_KEY || numkey_read() == '2'){
				NEXT_STATE = SHOW_TEMP_F;
				
				} if (numkey_read()== '1'){
				NEXT_STATE = SHOW_TEMP_C;
				
				} if (numkey_read() == '3'){
				NEXT_STATE = SHOW_TEMP_CF;
			}
			CURRENT_STATE = NEXT_STATE;
			break;	
			}
			
			case SHOW_TEMP_CF:
			sprintf(temp_str,"%u%cC " "%u%cF", temp_read_celsius(),
			 0xDF, temp_read_fahrenheit(), 0xDF);
			output_msg(p_str1, temp_str, 0);
			{
				if (numkey_read()== NO_KEY || numkey_read() == '3'){
					NEXT_STATE = SHOW_TEMP_CF;
					
					} if (numkey_read()== '2'){
					NEXT_STATE = SHOW_TEMP_F;
					
					} if (numkey_read() == '1'){
					NEXT_STATE = SHOW_TEMP_C;
				}
				CURRENT_STATE = NEXT_STATE;
				break;
			}
		}
		
    }
}

