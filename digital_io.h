#pragma once

#include "stm32l476xx.h"

class DigitalIO {

  public:
    enum pin {
      PA5, PA6, PA7,
      PB6
    };

  public:
    static void write(DigitalIO::pin pin, bool value);
    static bool read(DigitalIO::pin pin);

  private:
    static void enable_peripheral_bus(DigitalIO::pin pin);
    static void set_pin_mode(DigitalIO::pin pin, bool output);
    static int* get_bits_for_pin(DigitalIO::pin pin);
    static GPIO_TypeDef* get_GPIO_address(DigitalIO::pin pin);
};