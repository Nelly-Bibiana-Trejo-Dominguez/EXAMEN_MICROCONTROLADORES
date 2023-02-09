/*
 * ADC.c
 * ADC0 -
 */
#include "../include.h"


//////////lit todo puerto E y D para recibir señal, solo digo cuantos canales he de leer

extern void ADC_config_modulo_0(void)
{
    /////////////// PINES, Pag. 801
    // 1. RCGCADC
    SYSCTL->RCGCADC |= (1<<0) | (1<<1); // Habilita los modulos 0 y 1
    // 2. RCGCGPIO - PUERTO
    SYSCTL->RCGCGPIO |= (1<<4);  //E 4=E
    //SYSCTL->RCGCGPIO|= (1<<3);   //D  3=D
    // SYSCTL->RCGCGPIO|= (1<<1);   //B  1=B
    // 3. GPIOFSEL PAG. 801 - es 0 por ADC
    GPIOE->AFSEL |= (1<<3); // PIN (3)
    //GPIOD->AFSEL |= 0x0e;
    // GPIOE->AFSEL = (0<<3) | (0<<2) | (0<<1);    (PIN) (
    // GPIOD->AFSEL = (0<<3) | (0<<2) | (0<<1);    (PIN columna 3)
    // GPIOB->AFSEL = (0<<4) | (0<<5);
    // 4. GPIODEN 0: ANALÓGICO
    GPIOE->DEN &= (0<<3);
    //GPIOD->DEN &= ~0x0e;
    // GPIOE->DEN = (0<<3) | (0<<2) | (0<<1);
    // GPIOD->DEN = (0<<3) | (0<<2) | (0<<1);
    // GPIOB->DEN = (0<<4) | (0<<5);
    // 5. GPIOAMSEL
    GPIOE->AMSEL |= (1<<3);
    //GPIOD->AMSEL |= 0x0e;
    // GPIOB->AMSEL |= 0x0e;

    /////////////// SECUENCIADOR 0 Pag. 802 (espacios del secuenciador), 818
    // 1. ADCACTSS
    ADC0->ACTSS &= ~(1<<0);  // * 0 = Num. de secuenciador
    // 2. ADCEMUX
    ADC0->EMUX |= 0x0000; // * Cuándo leer
    // 3. ADCSSMUXn | CAMBIA DEPENDE DE LOS CANALES QUE SE DESEE LEER
            // NOTA: Para pasos 3, 4 las banderas dependen del número de canales.
    ADC0->SSMUX0 = (ADC0->SSMUX0 & 0x00000000) + 0;
     // ADC0->SSMUX0 = (ADC0->SSMUX0 & 0x00000000) + 0; // Limpia y suma el canal (en este caso el 0)
     // ADC0->SSMUX0 |= (1<<4); // canal 1(E) se recorre a 4 (se recorre cada 4 bits)
     // ADC0->SSMUX0 |= (2<<8); // canal 2(E) se recorre a 8
     // ADC0->SSMUX0 |= (6<<12); // canal 6(D) se recorre a 8
     // ADC0->SSMUX0 |= (5<<16); // canal 5(D) se recorre a 8

    // 4. ADCSSCTLn | BANDERAS DE INICIO Y FIN DE LECTURA QUE DEPENDE LOS CANALES QUE QUIERO LEER | se lee primero el IEX y el último es el ENDX
    ADC0->SSCTL0 |= (1<<1); // Pag. 868. 644 = núm en hexa para leer, en este caso esta leyendo los 4 canales. El primer 1 activa y el segundo es el bit
    //ADC0->SSCTL0 |= (1<<5);
    // 5. ADCIM
    ADC0->IM |= (0xf<<16) | (0xf<<0); // o puede ser: ~(1<<0) y 0=num. de secuenciador (y cambia dependiendo de este)
    // 6. ADCPP y ADCPC
    //ADC0_PP_R |= 0x7
    ADC0->PC |= 0x3; // Velocidad de muestras. Pag. 891 0x3=250 ksps
    // 7. ADCACTSS
    ADC0->ACTSS |= (1<<0); // Habilita el secuenciador. 0 = Número de secuenciador

//    /////////////// SECUENCIADOR 1
//      // 1. ADCACTSS
//      ADC1->ACTSS &= ~(1<<1); // 1 = Num. de secuenciador
//      // 2. ADCEMUX
//      ADC1->EMUX |= 0x0000;
//      // 3. ADCSSMUXn
//      // ADC1->SSMUX1 |= 0x0654;
//       ADC1->SSMUX1 = (ADC0->SSMUX1 & 0xFFFF0000) + 4; // Limpia y suma el canal (en este caso el 4)
//       ADC1->SSMUX1 |= (5<<4); // canal 5(B) se recorre a 4 (se recorre cada 4 bits)
//       ADC1->SSMUX1 |= (6<<8); // canal 6(B) se recorre a 8
//      // 4. ADCSSCTLn
//      ADC1->SSCTL1 |= 0x0644;
//      // 5. ADCIM
//      ADC1->IM|= (0xf<<16) | (0xf<<0);
//      // 6. ADCPP y ADCPC
//      //ADC0_PP_R |= 0x3
//      ADC1->PC |= 0x3;
//      // 7. ADCACTSS
//      ADC1->ACTSS |=(1<<1);

//      /////////////// SECUENCIADOR 2
//        // 1. ADCACTSS
//        ADC1->ACTSS &= ~(1<<2);
//        // 2. ADCEMUX
//        ADC1->EMUX |= 0x0000;
//        // 3. ADCSSMUXn
//        // ADC1->SSMUX2 |= 0x0654;
//        ADC1->SSMUX2 = (ADC1->SSMUX2 & 0xFFFF0000) + 4; // Limpia y suma el canal (en este caso el 4)
//        ADC1->SSMUX2 |= (5<<4); // canal 5(B) se recorre a 4 (se recorre cada 4 bits)
//        ADC1->SSMUX2 |= (6<<8); // canal 6(B) se recorre a 8
//        // 4. ADCSSCTLn
//        ADC1->SSCTL2 |= 0x2444;
//        // 5. ADCIM
//        ADC1->IM|= (0xf<<16) | (0xf<<0);
//        // 6. ADCPP y ADCPC
//        //ADC0_PP_R |= 0x3
//        ADC1->PC |= 0x3;
//        // 7. ADCACTSS
//        ADC1->ACTSS |=(1<<2);

//      /////////////// SECUENCIADOR 3
//        // 1. ADCACTSS
//        ADC1->ACTSS &= ~(1<<3);
//        // 2. ADCEMUX
//        ADC1->EMUX |= 0x0000;
//        // 3. ADCSSMUXn
//        // ADC1->SSMUX2 |= 0x0654;
//        ADC1->SSMUX3 = (ADC1->SSMUX3 & 0xFFFFFFF0) + 4; // Limpia y suma el canal (en este caso el 4)
//        // 4. ADCSSCTLn
//        ADC1->SSCTL3 |= 0x2;
//        // 5. ADCIM
//        ADC1->IM|= (0xf<<16) | (0xf<<0);
//        // 6. ADCPP y ADCPC
//        //ADC0_PP_R |= 0x3
//        ADC1->PC |= 0x3;
//        // 7. ADCACTSS
//        ADC1->ACTSS |=(1<<3);

}

/////////////////////////////////////////////////////////////////////////////////////////////////// RECIBIR CHAR UART
extern void ADC_leer_canal(uint16_t data[])
{
    ////SECUENCIADOR 0
    ADC0->PSSI |= (1<<0); // Indicador de lectira del indicador. 0 = Número de selector
    //SysTick_espera(.001);

    while (ADC0->RIS & 0x01 == 0);
    //SysTick_espera(.001);

    while(ADC0->SSOP0 & (1<<0) == (1<<0)); // Representativo de la espera entre cada canal, Pag. 863
    data[0] = ADC0->SSFIFO0 & 0xfff; // Poner lo del la FIFO
    //SysTick_espera(.001);
    while(ADC0->SSOP0 & (1<<4) == (1<<4));
    data[1] = ADC0->SSFIFO0 & 0xfff;
    //SysTick_espera(.001);
    while(ADC0->SSOP0 & (1<<8) == (1<<8));
    data[2] = ADC0->SSFIFO0 & 0xfff;
    //SysTick_espera(.001);

    ADC0->ISC |= (1<<0); // Limpiar el selector. 0 = Num. selector
    //SysTick_espera(.001);

//    ////Selector 1
//    ADC1->PSSI |= (1<<1);
//    SysTick_espera(.001);
//
//    while (ADC1->RIS & 0x02 == 0);
//    SysTick_espera(.001);
//    while(ADC1->SSOP1 & (1<<0) == (1<<0));
//    data[3] = ADC1->SSFIFO1 & 0xfff;
//    SysTick_espera(.001);
//    while(ADC1->SSOP1 & (1<<4) == (1<<4));
//    data[4] = ADC1->SSFIFO1 & 0xfff;
//    SysTick_espera(.001);
//    while(ADC1->SSOP1 & (1<<8) == (1<<8));
//    data[5] = ADC1->SSFIFO1 & 0xfff;
//    SysTick_espera(.001);
//
//    ADC1->ISC |= (1<<1);
//    SysTick_espera(.001);
//
//    ////Selector 2
//    ADC0->PSSI |= (1<<2);
//    SysTick_espera(.001);
//
//    while (ADC0->RIS & 0x01 == 0);
//    SysTick_espera(.001);
//
//    while(ADC0->SSOP0 & (1<<0) == (1<<0));
//    data[0] = ADC0->SSFIFO0 & 0xfff;
//    SysTick_espera(.001);
//    while(ADC0->SSOP0 & (1<<4) == (1<<4));
//    data[1] = ADC0->SSFIFO0 & 0xfff;
//    SysTick_espera(.001);
//    while(ADC0->SSOP0 & (1<<8) == (1<<8));
//    data[2] = ADC0->SSFIFO0 & 0xfff;
//    SysTick_espera(.001);
//
//    ADC0->ISC |= (1<<2);
//    SysTick_espera(.001);
}



