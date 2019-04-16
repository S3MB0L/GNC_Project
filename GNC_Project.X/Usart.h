/* 
 * File:   Usart.h
 * Author: Ugur
 *
 * Created on 11 Nisan 2019 Per?embe, 22:02
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif


void USART_Init(long);
void USART_TxChar(char);
char USART_RxChar();


#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

