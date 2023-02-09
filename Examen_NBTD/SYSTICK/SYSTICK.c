/*
 * SYSTICK.c
 *
 */

#include "../include.h"

extern void Configurar_SysTick(void){
    SysTick->CTRL = (0<<0); //Primero deshabilitamos el reloj (porque es un periferico apra darle la configuración
    SysTick->LOAD = 0x00FFFFFF - 1; //Configuramos el máximo valor de carga (24 bits - 1  porque empieza en *0*)
    SysTick->VAL = 0; //Empieza en 0
    SysTick->CTRL = (1<<0)                |          (1<<2);
    //           Habilita periferico         utiliza el reloj PLL configurable ( si es 0 utiliza el reloj de defecto de 16MHz)
}

extern void SysTick_espera(float delay){
    uint32_t i;
    for(i=0; i<(int)(delay*1000); i++){
        SysTick_ms(50000); //20 MHz a 1ms
    }
}

extern void SysTick_ms(uint32_t cuentas){
    SysTick->CTRL = (0<<0); //Primero deshabilitamos el reloj (porque es un periferico apra darle la configuración
    SysTick->LOAD = cuentas - 1; //Configuramos el máximo valor de carga (24 bits - 1  porque empieza en *0*)
    SysTick->VAL = 0; //Empieza en 0
    SysTick->CTRL = (1<<0)                |          (1<<2);
    //           Habilita periferico         utiliza el reloj PLL configurable ( si es 0 utiliza el reloj de defecto de 16MHz)
    //while((SysTick->CTRL & 0x10000) == 0){} // para verificar que aun no llega a la cuenta se monitorea el bit 16 = 0x10000, cuando el bit 16 = 1 llegó a la cuenta

}



