// includes low level peripheral definitions
#include "stm32l476xx.h"
#include "digital_io.h"

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
    uint8_t i = 0;
    while (true) {
        while(DigitalIO().read(DigitalIO::pin::PB6)) {
            DigitalIO().write(DigitalIO::pin::PA6, i & 0x1);
            DigitalIO().write(DigitalIO::pin::PA7, i & 0x2);
            i++;
            approx_wait(500);
        }
    }
}
