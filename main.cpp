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
    while (true) {
        DigitalIO().write(DigitalIO::pin::PA5, true);
        DigitalIO().write(DigitalIO::pin::PA6, true);
        DigitalIO().write(DigitalIO::pin::PA7, true);
        DigitalIO().write(DigitalIO::pin::PB6, true);
        approx_wait(500);

        DigitalIO().write(DigitalIO::pin::PA5, false);
        DigitalIO().write(DigitalIO::pin::PA6, false);
        DigitalIO().write(DigitalIO::pin::PA7, false);
        DigitalIO().write(DigitalIO::pin::PB6, false);
        approx_wait(500);
    }
}
