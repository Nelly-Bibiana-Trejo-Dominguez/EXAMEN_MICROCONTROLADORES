/*
 * UART.c
 *
 */


#include "../include.h"

extern void Configurar_UART3(uint32_t baudrate,uint32_t reloj){
    
    //Habilitar el reloj del uart y el del gpio con registros
    SYSCTL->RCGCUART |= (1<<3);   // | M3, o sea, UART 3 | C6, C7
    SYSCTL->RCGCGPIO |= (1<<2);   // PUERTO C - 0-A, 1-B, | C-2 |
    
    //Configurar el GPIO C
    GPIOC->AFSEL |= (1<<6) | (1<<7); // pines 6 & 7 - - 0: led, adc, 1: uart, pwm...
    //  GPIO        Rx       Tx
    GPIOC->DIR |= (0<<6) | (1<<7);   // 0: Entrada | 1: salida
    GPIOC->PUR |= (0<<6) | (0<<7);   // Sin resistencia pull up
    GPIOC->PDR |= (0<<6) | (0<<7);   // Sin resistencia pill down
    GPIOC->DEN |= (1<<6) | (1<<7);   // Pines digitales
    GPIOC->AMSEL = 0x00;             // Desactivamos la funcion analogica (no adc)
    GPIOC->PCTL = (GPIOC->PCTL & 0x00FFFFFF) | 0x11000000; // qué pines del puerto se configurar pag 689, 1351 (no olvidar que es en base al PIN)
                                 //Borrar      Escribir  7-6-5-4-...-0

    // *CONFIGURACION UARTX(3) - protocolo
    UART3->CTL |= (0<<8)| (0<<9)| (0<<0) | (0<<4);  //Limpiar los registros (desactivar uart, tx y rx) para configurarlos
    //            (TX)    (RX)   (UARTEN)   (EOT)

    // *Velocidad 115200 baudrate (velocidad de UART-transmision) , frecuencia de reloj 55 MHz (PLL)

    uint32_t BRD_I = reloj/(16 * baudrate);
    UART3->IBRD = BRD_I;
    uint32_t BRD_F = (float)reloj/(float)(16 * baudrate) - BRD_I;
    BRD_F = lround(BRD_F * 64 +0.5);
    UART3->FBRD = (int)BRD_F;
    UART3->LCRH = (0x3<<5)  | (1<<4);// Activa el fifo y el bit de paridad
    //habilitar_IntUART();
    UART3->CC = 0x00;    // reloj pag939 0x00 System clock
    UART3->CTL |= (1<<8)| (1<<9)| (1<<0) | (1<<4); //Limpiar los registros (activar uart, tx y rx)
}

// *Interrupción UART FIFO
extern void habilitar_IntUART(void){
    UART3->IFLS = (UART3->IFLS & 0x00)| 0x04; //ver pagina 922 data (activar interrupcion Rx >= 1/8llena Tx <= 1/8 vacia )
    UART3->IM |= (1<<4) | (1<<5); //que tipo de interrupciones poner (Que interrumpa por transmiciï¿½n o recepciï¿½n)(siempre por la pila ver arriba)) 924
    //habilitar interrupciones//
    // numero de interrupcuï¿½in uart0 pag 104 interrupciï¿½n 5, prioridad(PRI) = 5/4 = 1 ... PRI1_R
    //[4n+3] [4n+2] [4n+1] [4n]
    // FF       FF    00    FF /el que quiero 4*1+1=5 pag 152
    //PRI = IP & EN= ISER ??
//    NVIC->IP[14] = (NVIC->IP[14] & 0x00FFFFFF) | (0X40000000);; // jerarquï¿½a 2... bit 13, 14 y 15 (13=0 14=1 15=0... binario 010 = 2) pagina 152 para ver vectores
//    NVIC->ISER[1] =(1<<27); // interrupcion 5 (un 1 en el bit 5) = 0x20
    NVIC_SetPriority (UART3_IRQn, 1);
    NVIC_EnableIRQ (UART3_IRQn);
}

extern char Rx_char(void){ //leemos n caracter
    int32_t v;
    char c;
    while((UART3->FR & (1<<4))!=0); //FR pag 911 flag de bandera
    v = UART3->DR & 0xFF;  // Dr 906
    c = v;
    return c;
}

extern char * Rx_string(char limit){ //leemos una cadena
    uint32_t i=0;
    char *string = (char*)calloc(10,sizeof(char));
    char c = Rx_char();
    while(c != limit){
        *(string + i) = c;
        i++;
        if(i%10==0){
            string = realloc(string,(i+10)*sizeof(char));
        }
        c = Rx_char();
    }
    return string;
}

extern char * Rx_string2(char string[], uint8_t len){ //leemos una cadena
    uint32_t i=0;
    do
        {
                string[i] = Rx_char();
                if (string[i] == '%')
                {
                    if (string[i-1] == '\r' && i > 1)
                    {
                        string[i-1] = '\0';
                    }
                    else
                    {
                        string[i] = '\0';
                    }
                    break;
                }
                i ++;

        }while (i < len);
        string[len-1] = '\0';
    }

// TRANSMISION
extern void Tx_char(char c){ //enviamos un caracter
    while((UART3->FR & (1<<5))!=0);
    UART3->DR = c;
}


extern void Tx_string(char *cadena){ //enviamos una cadena
    while(*cadena){
        Tx_char(*(cadena++));
    }
    Tx_char('\n');
}

extern char * invertir_string(char *str){ //invertimos una cadena
    uint32_t n = strlen(str);
    uint32_t i = 0;
    char *inv = (char*)calloc(10,sizeof(char));
    while(i<n){
        *(inv + (n-i-1)) = str[i];
        i++;
        if(i%10==0){
             inv = realloc(inv,(i+10)*sizeof(char));
        }
    }
    return inv;
}







