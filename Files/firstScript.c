#include <stdio.h>
#include <stdint.h>

#include "inc/tm4c1294ncpdt.h"

int main(void){

    SYSCTL_RCGCGPIO_R = 0x3615;  /* Enable Clock to GPIOE or PE3/AN0 */
    SYSCTL_RCGCADC_R = 0x01;    /* AD0 clock enable*/

    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR; // encender PLL
    while((SYSCTL_PLLSTAT_R&0x01)==0);           // espera a que el PLL fije su frecuenc
    SYSCTL_PLLFREQ0_R &= ~SYSCTL_PLLFREQ0_PLLPWR;// apagar PLL

    GPIO_PORTK_DIR_R = 0x00; // Port K0 and K1 as INPUT
    GPIO_PORTK_DEN_R = 0x03; // Port K0 and K1 with digital function

    GPIO_PORTN_DIR_R = 0x30; // Port N4 and N5 as output
    GPIO_PORTN_DEN_R = 0x30; // Port N4 and N5 with digital function

    while(1){
        if(GPIO_PORTK_DATA_R == 1){
            GPIO_PORTN_DATA_R = 0x10;
        }else if(GPIO_PORTK_DATA_R == 2){
            GPIO_PORTN_DATA_R = 0x20;
        }else{
            GPIO_PORTN_DATA_R = 0x00;
        }
    }
    printf("Hello you\n");

	return 0;
}