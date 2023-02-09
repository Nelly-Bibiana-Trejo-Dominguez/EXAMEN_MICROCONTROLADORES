/*
 * UART.h
 *
 */

#ifndef UART_UART_H_
#define UART_UART_H_

extern void Configurar_UART0(uint32_t baudrate,uint32_t reloj);
extern void Configurar_UART3(uint32_t baudrate,uint32_t reloj);
extern void habilitar_IntUART(void);
extern char Rx_char(void);
extern void Tx_char(char c);
extern char * Rx_string(char deli); //deli= delimita la cadena para saber hasat donde leer
extern void Tx_string(char *cadena);
extern char * invertir_string(char *str);

#endif /* UART_UART_H_ */
