#include "include.h"


 // CONFIGURAR EL puerto A

extern void ConfigurarGPIOA(void)
{
    SYSCTL->RCGCGPIO|= (1<<0); // Habilita (1) el puerto A(0)  | 0-A |
    //GPIOB->LOCK      = 0x4C4F434B;  // Para puero F y D7 se habilita
    //GPIOB->CR        = (1<<3);      // Para puero F y D7 se habilita
    GPIOA->DIR      |= (0<<3); // El 3 cambia dependiendo del PIN dado | ENTRADA
    GPIOA->DEN      |= (1<<3);
    GPIOA->AFSEL    |= (0<<3);
    GPIOA->PUR      |= (1<<3);



    NVIC_SetPriority(GPIOA_IRQn, 0); //PRI=4 el 0 con mayor prioridad el 7 con menos
    NVIC_EnableIRQ(GPIOA_IRQn);

    // El 3 cambia dependiendo el PIN
    GPIOA->IM  |= (0<<3); // Masked
    GPIOA->IS  |= (0<<3); // Edge-sensitive
    GPIOA->IBE |= (1<<3); // Both edges, ambos flancos
    // GPIOA->IEV |= (0<<3); // mientras esté presionado (un cambio)
    GPIOA->RIS |= (0<<3); // Registro de estado INICIALIZAR, o sea, poner a 0
    GPIOA->IM  |= (1<<3); // Send
}

//extern void Configurar_LED_TIVA(void)  // F
//{
//    SYSCTL->RCGCGPIO|= (1<<5); // Habilita (1) el puerto A(0)  | 0-A | F PARA LED DE TIVA
//    GPIOB->LOCK      = 0x4C4F434B;  // Para puero F y D7 se habilita
//    //GPIOB->CR        = (1<<0);      // Para puero F y D7 se habilita
                      //  RED      GREEN      BLUE
//    GPIOA->DIR      = (1<<3) | (1<<2) | (1<<1); // El 3 cambia dependiendo del PIN dado | ENTRADA
//    GPIOA->DEN      = (1<<3) | (1<<2) | (1<<1);
//    GPIOA->AFSEL    = (0<<3) | (0<<2) | (0<<1);
//    GPIOB->LOCK      = 0x11111111;
//}

extern void Configurar_LED_EXT(void) // B1
{
    SYSCTL->RCGCGPIO|= (1<<1); // Habilita (1) el puerto A(0)  | 0-A | F PARA LED DE TIVA
    //GPIOB->LOCK      = 0x4C4F434B;  // Para puero F y D7 se habilita
    //GPIOB->CR        = (1<<3);      // Para puero F y D7 se habilita
    GPIOB->DIR      |= (1<<1); // El 3 cambia dependiendo del PIN dado | ENTRADA primer 1, es salida
    GPIOB->DEN      |= (1<<1);
    GPIOB->AFSEL    |= (0<<1);
}

//extern void Delay(void)
//{
//  unsigned long volatile time;
//  time = 1600000;
//  while(time)
//  {
//        time--;
//  }
//}
