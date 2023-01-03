/*
 * my test code.c
 *
 * Created: 12/28/2022 10:17:28 AM
 * Author : Ahmed Hassan
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "avr/delay.h"
#include "LCD.h"
#include "ADC.h"
#define degree 0xDF
char Temperature;


int main(void)
{
	DIO_SET_PIN_DIR('D',0,1);
	DIO_SET_PIN_DIR('D',1,1);
    LCD_intial();
	ADC_vinit();
	LCD_send_string("Temperature=");
    while (1) 
    {
		Temperature = (ADC_u16Read()*0.25);
		if (Temperature<10)
		{
			LCD_move_cursor(1,13);
			//LCD_send_char('0');
			LCD_send_char(Temperature+48);
			LCD_send_char(degree);
			LCD_send_char('C');
			LCD_send_char(0x20);
		}
		else if (Temperature<100)
		{	
			LCD_move_cursor(1,13);
			LCD_send_char((Temperature/10)+48);
			LCD_send_char((Temperature%10)+48);
			LCD_send_char(degree);
			LCD_send_char('C');
			if(Temperature<20)
			{
				DIO_WRITE_PIN('D',1,1);
				
				
			}
			else if (Temperature>30)
			{
				DIO_WRITE_PIN('D',0,1);
				
			}
			else
			{
				DIO_WRITE_PIN('D',0,0);
				DIO_WRITE_PIN('D',1,0);
			}
		}
    }
}

