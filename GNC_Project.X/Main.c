/* 
 * File:   Main.c
 * Author: Ugur Ozkan
 *
 * Created on 14 Nisan 2019 Pazar, 03:19
 */

#include <pic18f4550.h>
#include "XC8_Config.h"
#include "LCD_16x2_8bit.h"
#include "Usart.h"

#define LED_1   PORTAbits.RA2
#define LED_2   PORTAbits.RA3

#define BUTON0  PORTCbits.RC0
#define BUTON1  PORTAbits.RC1

char data_in;
char Count_1;
char Count_2;
char Count_3;

void System_Init();

int main() {
    
    ADCON1 = 0x0F;
    OSCCON = 0x72;
    
    TRISAbits.RA2 = 0;
    TRISAbits.RA3 = 0;
    
    TRISCbits.TRISC0 = 1;
    BUTON0 = 0;
    
    LED_1 = 0;
    LED_2 = 0;
    
    USART_Init(9600);         
    LCD_Init();
    LCD_Clear();
    __delay_ms(100);
    
    System_Init();   
    while(1){
        
        data_in = USART_RxChar();
        __delay_ms(50);
        
        USART_TxChar(data_in);
        
        LCD_Clear();
        
        if (BUTON0 == 1) {
        /*
            To-Do:
            if kısmını binary tip te ve define olmadan deneyelim
            if(PORTCbits.RC0 == 0b00000001 veya PORTC == 0b00000001) { ... } şeklinde
            #include <stdio.h>
            #include <stdlib.h> ile standart c kütüphanlerini ekleyelim debug için
            
            portun durumunu sprintf ile lcd ye yazdıralım
            sprintf(buffer,"%x",PORTCBits.RC0); ile
            LCD_String(buffer); ile ekrana yazdıralım 
            Debug aracında portc registerini izlersek daha güzel olur tabi
        */
            Count_3++;
            
            if (Count_3 == 1) {
                LCD_Clear();
                LCD_String("Butona Basildi 1");
                USART_TxChar('1');
                LED_1 = 1;
            }
            if (Count_3 == 2) {
                LCD_Clear();
                LCD_String("Butona Basildi 2");
                USART_TxChar('1');
                LED_1 = 0;
                Count_3=0;

            }
        }
        /*
            To-Do:
            buraya yukarıdaki if deyimine karşılık else if ve else ekleyelim
            if(PORTC == 0b00000001 veya Button0==1)
            {...}
            else if(PORTC = 0b00000000 veya Button0==0)
            {Burada LCD ye portc=0 diye yazdırabiliriz...}
            burada iki kod bloğu da çalışmadığı durumda pin konfigrasyonuyla yada 
            compilerle alakalı bir sorun oldğunu anlamış oluruz ve o hatayı yazdırırız.
            else
            {LCD PORTC error...}
        */
        
        if (data_in == '1') {
            Count_1++;
            
            if (Count_1 == 1) {
                
                LCD_Clear();
                __delay_ms(100);
                LCD_String_xy(1,4,"LED_1 ON");
                LED_1 = 1;
               
            }
            
            if (Count_1 == 2) {
                
                LCD_Clear();
                __delay_ms(100);
                LCD_String_xy(1,3,"LED_1 OFF");
                Count_1 = 0;
                LED_1 = 0;
                           
            }

        }
        
        if (data_in == '2') {
            
            Count_2++;
            
            if (Count_2 == 1) {
                
                LCD_Clear();
                __delay_ms(100);
                LCD_String_xy(1,4,"LED_2 ON");
                LED_2 = 1;
          
            }
            
            if (Count_2 == 2) {
                LCD_Clear();
                __delay_ms(100);
                LCD_String_xy(1,3,"LED_2 OFF");
                Count_2 = 0;
                LED_2 = 0;
                      
            }
        } 
    }
}


void System_Init(){
    
    LCD_String_xy(1,0,"Sistem Basliyor");
    __delay_ms(2000);
    LCD_Clear();
    __delay_ms(100);
    LCD_String_xy(1,2,"Gonca Sahin");
    __delay_ms(100);
    LCD_String_xy(2,3,"SDU Proje");
    __delay_ms(2000);
    LCD_Clear();
    __delay_ms(100);
    LCD_String_xy(1,4,"Prof.Dr");
    __delay_ms(100);
    LCD_String_xy(2,1,"Selcuk Comlekci");
    __delay_ms(2000);
    LCD_Clear();
    __delay_ms(100);
    
    LCD_String_xy(1,1,"Cihaz Baglandi");
    LCD_String_xy(2,0,"Butona Basiniz!!");        
    __delay_ms(1000);
    
}

