#include "XC8_Config.h"
#include "Usart.h"
#include <pic18f4550.h>

#define F_CPU 8000000/64

#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

/*****************************USART Initialization*******************************/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6=0;                       /*Make Tx pin as output*/
    TRISC7=1;                       /*Make Rx pin as input*/
    temp=Baud_value;     
    SPBRG=(int)temp;                /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA=0x20;                     /*Transmit Enable(TX) enable*/ 
    RCSTA=0x90;                     /*Receive Enable(RX) enable and serial port enable */
}
/******************TRANSMIT FUNCTION*****************************************/ 
void USART_TxChar(char out)
{        
    while(TXIF==0);            /*wait for transmit interrupt flag*/
    TXREG=out;                 /*transmit data via TXREG register*/    
}
/*******************RECEIVE FUNCTION*****************************************/
char USART_RxChar()
{

    while(RCIF==0);       /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);   /*receive data is stored in RCREG register and return */
}

