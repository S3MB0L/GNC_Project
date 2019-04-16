#include <pic18f4550.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "LCD_16x2_8bit.h"
#include "XC8_Config.h"

#define LCD_RS      LATC1                                                       /* PORTC 6 pin is used for Register Select */
#define LCD_EN      LATC2                                                       /* PORTC 7 pin is used for Enable */
#define LCD_Data    LATD                                                        /* PORTD is used for transmitting data to LCD */

#define LCD_Port    TRISD              
#define LCD_Control TRISC

#define TRUE        1
#define FALSE       0

/*********************************Functions*************************************/

void LCD_Init(){
    
    __delay_ms(15);                                                             /* 15ms,16x2 LCD Power on delay */
    LCD_Port = 0x00;                                                            /* Set PORTD as output PORT for LCD data(D0-D7) pins */
    LCD_Control = 0x00;                                                         /* Set PORTC as output PORT LCD Control(RS,EN) Pins */
    LCD_Command(0x38);                                                          /* uses 2 line and initialize 5*7 matrix of LCD */
    LCD_Command(0x01);                                                          /* clear display screen */
    LCD_Command(0x0c);                                                          /* display on cursor off */
    LCD_Command(0x06);                                                          /* increment cursor (shift cursor to right) */
}

/*******************************************************************************/

void LCD_Clear(){
    
    LCD_Command (0x01);                                                          /* clear display screen */
}

void LCD_Command(char cmd ){
    
	LCD_Data = cmd;                                                             /* Send data to PORT as a command for LCD */   
	LCD_RS = 0;                                                                 /* Command Register is selected */
	LCD_EN = 1;                                                                 /* High-to-Low pulse on Enable pin to latch data */ 
	NOP();
	LCD_EN = 0;
	__delay_ms(3);	
}

void LCD_Char(char dat){
    
	LCD_Data = dat;                                                             /* Send data to LCD */  
	LCD_RS = 1;                                                                 /* Data Register is selected */
	LCD_EN = 1;                                                                 /* High-to-Low pulse on Enable pin to latch data */   
	NOP();
	LCD_EN = 0;
	__delay_ms(1);
}

void LCD_String(const char *msg){
    
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
}

void LCD_String_xy(char row,char pos,const char *msg){
    
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);                                       /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);                                       /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    LCD_String(msg);
}

