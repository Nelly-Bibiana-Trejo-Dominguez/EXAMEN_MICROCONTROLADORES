/*
 * SYSTICK.h
 *
 */

#ifndef SYSTICK_SYSTICK_H_
#define SYSTICK_SYSTICK_H_


extern void Configurar_SysTick(void);
extern void SysTick_ms(uint32_t cuentas);
extern void SysTick_espera(float delay);


#endif /* SYSTICK_SYSTICK_H_ */
