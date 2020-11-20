#include "digital_io.h"

void DigitalIO::write(DigitalIO::pin pin, bool value) {
  GPIO_TypeDef * GPIOx = get_GPIO_address(pin);

  enable_peripheral_bus(pin);
  set_pin_mode(pin, true);

  GPIOx->BSRR |= 1 << get_bits_for_pin(pin)[(value ? 3 : 4)]; // (p306)
}

bool DigitalIO::read(DigitalIO::pin pin) {
  GPIO_TypeDef * GPIOx = get_GPIO_address(pin);
  
  enable_peripheral_bus(pin);
  set_pin_mode(pin, false);

  return (GPIOx->ODR & (1 << get_bits_for_pin(pin)[5])) >> get_bits_for_pin(pin)[5];
}

void DigitalIO::enable_peripheral_bus(DigitalIO::pin pin) {
  RCC->AHB2ENR |= 1 << get_bits_for_pin(pin)[0]; // (p261)
}

void DigitalIO::set_pin_mode(DigitalIO::pin pin, bool output) {
  GPIO_TypeDef * GPIOx = get_GPIO_address(pin);
  
  GPIOx->MODER &= ~(1 << get_bits_for_pin(pin)[1]);
  GPIOx->MODER |= output << get_bits_for_pin(pin)[2]; // (p303)
}

int* DigitalIO::get_bits_for_pin(DigitalIO::pin pin) {
  /*
  [peripheral bit, GPIOx_MODER bit 1, GPIOx_MODER bit 2, GPIOx_BSRR set bit, GPIOx_BSRR reset bit, GPIOx_IDR bit]
  [p306          , p303             , p303             , p306              , p306                , p305         ]
  */

  if (pin == DigitalIO::PA5) return &(new (int[6]) { 0, 11, 10, 5, 21, 5 })[0];
  if (pin == DigitalIO::PA6) return &(new (int[6]) { 0, 13, 12, 6, 22, 6 })[0];
  if (pin == DigitalIO::PA7) return &(new (int[6]) { 0, 15, 14, 7, 23, 7 })[0];

  if (pin == DigitalIO::PB6) return &(new (int[6]) { 1, 13, 12, 6, 22, 6 })[0];

  return nullptr;
}

GPIO_TypeDef* DigitalIO::get_GPIO_address(DigitalIO::pin pin) {
  int bit = get_bits_for_pin(pin)[0];

  if (bit == 0) return GPIOA;
  if (bit == 1) return GPIOB;

  return nullptr;
}