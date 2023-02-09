

/**
 * main.c
 */
#include "include.h"

#define canales    1        ///defino cuantos canales he de leer
uint16_t adc_data[canales] = {0};   // arreglos de enteros con 4 casillas, por canal
uint8_t i = 0;

char data_str[64] = " " ;

void Delay(void){
  unsigned long volatile time;
  time = 100000;
  while(time){
        time--;
  }
}



int main(void)
{

    Configurar_PLL(); // 55

//#define SYSCTL_RCC2_USERCC2     0x80000000  // Use RCC2
//#define SYSCTL_RCC2_DIV400      0x40000000  // Divide PLL as 400 MHz vs. 200
//#define SYSCTL_RCC2_SYSDIV2_M   0x0FC00000  // System Clock Divisor 2
//
//    int clk = 0, d = 0,     data = 0x3; // 8 bits data
//        int USERCC2 = SYSCTL->RCC2 & SYSCTL_RCC2_USERCC2;
//        int DIV400  = SYSCTL->RCC2 & SYSCTL_RCC2_DIV400;
//
//        //obtiene la frecuencia del SYSTEM CLOCK
//        if(USERCC2 == SYSCTL_RCC2_USERCC2){
//            d = (SYSCTL->RCC2) & SYSCTL_RCC2_SYSDIV2_M;
//            d = (d >> 22) + 1;
//            if(DIV400 == SYSCTL_RCC2_DIV400){
//                clk = 400000000 / d;
//            }
//            else if(DIV400 == 0) clk = 200000000 / d;
//        }
//        else clk = 16000000;

    Configurar_UART3(115200,57142857);
    ConfigurarGPIOA();
    // Configurar_LED_TIVA();
    Configurar_LED_EXT();

    ADC_config_modulo_0();


	while(1U){


 	    ADC_leer_canal(adc_data);
 	 //  Delay();

 	    // Para cada canal
        duty0 =  adc_data[0] ; /// E3
        duty1 =  adc_data[1] ; ///E2
        duty2 =  adc_data[2] ; ///E1
        duty3 =  adc_data[3] ; ///D3
        duty4 =  adc_data[4] ; /// D2
        duty5 =  adc_data[5] ; ///D1


        ///////////////////// enviar datos

///////comentar o descomentar para saber cuál graficar.
    /*  sprintf(data_str, "%04u", duty0);
        Tx_string(data_str); */
       /*  sprintf(data_str, "%04u", duty1);
           Tx_string(data_str); */
//             sprintf(data_str, "%04u", adc_data[0]);
//               Tx_string(data_str);
            /*   sprintf(data_str, "%04u", duty3);
                  Tx_string(data_str); */
                /*   sprintf(data_str, "%04u", duty4);
                      Tx_string(data_str); */
                    /*   sprintf(data_str, "%04u", duty5);
                         Tx_string(data_str); */



	}
}

// INTERRUPCION
// Recordar agregar el nombre de la funcion en el archivo startup en el UART que se este utilizando
extern void UART(void){
    if(UART3->RIS & (1<<4)){
        char * UART3_String[10];
        Rx_string2(UART3_String, 10); //LEER
        UART3->ICR |= (1<<4);  // LIMPIAR
    }
    if(UART3->RIS & (1<<5)){ // ENVÍA
        UART3->ICR |= (1<<5); // LIMPIAR
    }
}

// AL apretar boton enviar dato
extern void Enviar_dato(void){
    if ((GPIOA->RIS & (1<<3)) == (1<<3)){
        ltoa(adc_data[0], data_str, 10); //10=ver en decimal
        Tx_string(data_str);

        int level = 4095/2;
        if(adc_data[0]>=level){
            GPIOB->DATA=(1<<1);

        }
        else{
            GPIOB->DATA=(0<<1);
        }

        GPIOA->ICR |= (1<<3); // LIMPIAR
        Delay();

    }
}


