/*
 * PWM.c
 *
 */
#include "../include.h"

extern void Configurar_PWM0(void){
    /*
     * 10 khz con 50Mhz en el reloj  <---------EXP1
     *     */
    SYSCTL->RCGCPWM |= (1<<0); //Habilitar el periferico PWM
    SYSCTL->RCGC0 |= (1<<20); //habilita el pin default
    SYSCTL->RCGCGPIO |= (1<<1); //habilitar el PUERT0 asociado al modulo 0 y generador 1 pag 1233
    SYSCTL->RCGC2 |= (1<<1); //Puerto B
    GPIOB->AFSEL |= (1<<6); //Activar la función alternativa del pin PB6
    GPIOB->DEN |= (1<<6);    //digital
    GPIOB->PCTL |= (GPIOB->PCTL & 0xF0FFFFFF) | 0x04000000; //que pines del puerto se configurar pag 1351

    SYSCTL->RCC &= ~(0x000e0000); //limpio
    SYSCTL->RCC |= (1<<20); //Para indicarle que el reloj del PWM NO voy a dividirlo
    SYSCTL->RCC |= (0x3<<17); //si se dividiera: Divisor entre 16, por lo tanto 20,000,000/16= 1 250 000 Hz PAG 255   <----------50

   // SYSCTL->RCC &= ~(1<<20); //Para indicarle que el reloj del PWM NO voy a dividirlo  &= ~(1<<20);
   // SYSCTL->RCC &= ~(0b100<<17); //si se dividiera: Divisor entre 32, por lo tanto 80,000,000/32 = 2,500,000 Hz PAG 255   <----------50

    PWM0->_0_CTL &= ~(1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
    PWM0->_0_CTL &= ~(1<<1); //habilitar este registro para poder usarlo el PWM pag 1270
                               //cuenta hacia arriba  por habilitar 1 desplazado en 1
    PWM0->_0_GENA |= 0x08C; //ver pag 1283 para ver la configuración 10 00 00 00 11 00
                    //bit 11-10 comparador B = 0x2 = 0b10 cundo llegue al valor de comparación va a bajar a 0
                    // C si contara ahcia abajo
    PWM0->_0_LOAD = 25000-1; //Cuentas para que sea de 50hz // cuentas = Fclk/Fpwm   (1/f) / (1/clck) 5000-1<___EXP1
    PWM0->_0_CMPA = 0 ; //Para que el ciclo de trabajo activo sea de: %
    PWM0->_0_CTL |= (1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
    PWM0->ENABLE |=(1<<0); //HABILITA LA SALIDA DEL PWM del generador A modulo 0 y generador B modulo 0
}



extern void Configurar_PWM3(void){
    /*
     * 10 khz con 50Mhz en el reloj  <---------EXP1
     *     */
    SYSCTL->RCGCPWM |= (1<<0); //Habilitar el periferico PWM
    SYSCTL->RCGC0 |= (1<<20); //habilita el pin default
    SYSCTL->RCGCGPIO |= (1<<1); //habilitar el PUERT0 asociado al modulo 0 y generador 1 pag 1233
    SYSCTL->RCGC2 |= (1<<1); //Puerto B
    GPIOB->AFSEL |= (1<<5); //Activar la función alternativa del pin PB5
    GPIOB->DEN |= (1<<5);    //digital
    GPIOB->PCTL |= (GPIOB->PCTL & 0xFF0FFFFF) | 0x00400000; //que pines del puerto se configurar pag 1351

    SYSCTL->RCC &= ~(0x000e0000); //limpio
    SYSCTL->RCC |= (1<<20); //Para indicarle que el reloj del PWM NO voy a dividirlo
    SYSCTL->RCC |= (0x3<<17); //si se dividiera: Divisor entre 16, por lo tanto 20,000,000/16= 1 250 000 Hz PAG 255   <----------50

    PWM0->_1_CTL &= ~(1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
    PWM0->_1_CTL &= ~(1<<1); //habilitar este registro para poder usarlo el PWM pag 1270
                               //cuenta hacia arriba  por habilitar 1 desplazado en 1
    PWM0->_1_GENB |= 0x80C; //ver pag 1283 para ver la configuración 10 00 00 00 11 00
                    //bit 11-10 comparador B = 0x2 = 0b10 cundo llegue al valor de comparación va a bajar a 0
                    // C si contara ahcia abajo
    PWM0->_1_LOAD = 25000-1; //Cuentas para que sea de 50hz // cuentas = Fclk/Fpwm   (1/f) / (1/clck) 5000-1<___EXP1
                             // para el EXP2 (20MHz/16) / (50-11)
    PWM0->_1_CMPB = 0 ; //Para que el ciclo de trabajo activo sea de: %
    PWM0->_1_CTL |= (1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
    PWM0->ENABLE |=(1<<3); //HABILITA LA SALIDA DEL PWM del generador A modulo 0 y generador B modulo 0
}

extern void Configurar_PWM5(void){
    /*
    EXP2y3
     */
    SYSCTL->RCGCPWM |= (1<<0); //Habilitar el periferico PWM
    SYSCTL->RCGC0 |= (1<<20); //habilita el pin default
    SYSCTL->RCGCGPIO |= (1<<4); //habilitar el PUERT0 asociado al modulo 0 y generador 1 pag 1233
    SYSCTL->RCGC2 |= (1<<4); //Puerto E
    GPIOE->AFSEL |= (1<<5); //Activar la función alternativa del pin PE5
    GPIOE->DEN |= (1<<5);    //digital
    GPIOE->PCTL |= (GPIOE->PCTL & 0xFF0FFFFF) | 0x00400000; //que pines del puerto se configurar pag 1351

    SYSCTL->RCC &= ~(0x000e0000); //limpio
    SYSCTL->RCC |= (1<<20); //Para indicarle que el reloj del PWM  voy a dividirlo
    SYSCTL->RCC |= (0x3<<17); //Divisor entre 16, por lo tanto 20,000,000/16= 1 250 000 Hz PAG 255   <----------50

    //SYSCTL->RCC &= ~(1<<20); //Para indicarle que el reloj del PWM NO voy a dividirlo
    //SYSCTL->RCC &= ~(0b100<<17); //si se dividiera: Divisor entre 32, por lo tanto 80,000,000/32 = 2,500,000 Hz PAG 255   <----------50

    PWM0->_2_CTL &= ~(1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
    PWM0->_2_CTL &= ~(1<<1); //habilitar este registro para poder usarlo el PWM pag 1270
                               //cuenta hacia arriba  por habilitar 1 desplazado en 1
    PWM0->_2_GENB |= 0x80C; //ver pag 1283 para ver la configuración 10 00 00 00 11 00
                    //bit 11-10 comparador B = 0x2 = 0b10 cundo llegue al valor de comparación va a bajar a 0
                    // C si contara ahcia abajo
    PWM0->_2_LOAD = 25000-1; //Cuentas para que sea de 50hz // cuentas = Fclk/Fpwm   (1/f) / (1/clck) 5000-1<___EXP1
    PWM0->_2_CMPB = 12500-1; //Para que el ciclo de trabajo activo sea de: %
    PWM0->_2_CTL |= (1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
    PWM0->ENABLE |=(1<<5); //HABILITA LA SALIDA DEL PWM del generador A modulo 0 y generador B modulo 0
}

extern void Configurar_PWM6(void){


    SYSCTL->RCGCPWM |= (1<<0); //Habilitar el periferico PWM
        SYSCTL->RCGC0 |= (1<<20); //habilita el pin default
        SYSCTL->RCGCGPIO |= (1<<5); //habilitar el PUERT0 asociado al modulo 0 y generador 1 pag 1233
        SYSCTL->RCGC2 |= (1<<5); //Puerto F
        GPIOE->AFSEL |= (1<<2); //Activar la función alternativa del pin PF2
        GPIOE->DEN |= (1<<2);    //digital
        GPIOE->PCTL |= (GPIOE->PCTL & 0xFFFFF0FF) | 0x00000400; //que pines del puerto se configurar pag 1351

        SYSCTL->RCC &= ~(0x000e0000); //limpio
           SYSCTL->RCC |= (1<<20); //Para indicarle que el reloj del PWM NO voy a dividirlo
           SYSCTL->RCC |= (0x3<<17); //si se dividiera: Divisor entre 16, por lo tanto 20,000,000/16= 1 250 000 Hz PAG 255   <----------50

        PWM1->_3_CTL &= ~(1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
        PWM1->_3_CTL &= ~(1<<1); //habilitar este registro para poder usarlo el PWM pag 1270
                                   //cuenta hacia arriba  por habilitar 1 desplazado en 1
        PWM1->_3_GENA |= 0x08C; //ver pag 1283 para ver la configuración 10 00 00 00 11 00
                        //bit 11-10 comparador B = 0x2 = 0b10 cundo llegue al valor de comparación va a bajar a 0
                        // C si contara ahcia abajo
        PWM1->_3_LOAD = 25000-1; //Cuentas para que sea de 50hz // cuentas = Fclk/Fpwm   (1/f) / (1/clck) 5000-1<___EXP1
        PWM1->_3_CMPB = 2500-1 ; //Para que el ciclo de trabajo activo sea de: %
        PWM1->_3_CTL |= (1<<0); //deshabilitar este registro apra poder configurar el PWM pag 1270
        PWM1->ENABLE |=(1<<6); //HABILITA LA SALIDA DEL PWM del generador A modulo 0 y generador B modulo 0
    }
    /*
     * Usando el modulo 1 y generador 3 y comparador B con una frecuencia de trabajo de 1kHz
     * y un duty cycle de 20% en alto usando como fuente de reloj la velocidad de la tarjeta 80Mhz
     */


extern void PWM0_GEN0_ISR(void){

}


