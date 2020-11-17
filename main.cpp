// includes low level peripheral definitions
#include "stm32l476xx.h"

/**
 * Waits for an approximate number of milliseconds, this function blocks the CPU
 * 
 * @param milliseconds to wait
 */
void approx_wait(uint32_t milliseconds)
{
    for (uint32_t j = 0; j < milliseconds; j++)
    {
        for (volatile uint32_t i = 0; i < 4000; i++)
            ;
    }
}

int main()
{    
    //Green led of the NUCLEO-L476RG is connected to PA5
    //Enable GPIOA peripheral in the AHB2ENR: set bit 0
    RCC->AHB2ENR |= 1;
    
    // GPIOA_MODER set GP output mode: reset bit 11 & set bit 10
    GPIOA->MODER &= ~(1<<11);
    GPIOA->MODER |= 1 << 10;
    
    // GPIOA_OTYPER pushpull: default after reset
    // GPIOA_OSPEEDR low speed: default after reset
    // GPIOA_PUPDR no pull-up / no pull-down: default after reset

    while (true)
    {
        //GPIOA_BSRR set pin 5: set bit 5
        GPIOA->BSRR |= 1<< 5;
        approx_wait(500);
        //GPIOA_BSRR reset pin 5: set bit 21
        GPIOA->BSRR |= 1 << 21;
        approx_wait(500);
    }
}
