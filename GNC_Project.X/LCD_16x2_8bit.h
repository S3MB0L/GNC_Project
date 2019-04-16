/* 
 * File:   LCD_16x2_8bit.h
 * 
 * Author: Ugur OZKAN
 *
 * Created on 11 Nisan 2019 Per?embe, 18:58
 */

#ifndef LCD_2X16_H
#define	LCD_2X16_H

#ifdef	__cplusplus
extern "C" {
#endif


void LCD_Init();
void LCD_Clear();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);    


#ifdef	__cplusplus
}
#endif

#endif	/* LCD_2X16_H */

