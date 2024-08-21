/**************************************************************
 * main.c
 * rev 1.0 21-Aug-2024 owner
 * Lab4
 * ***********************************************************/


#include <stdint.h> 
#include <stdbool.h>
#include <stdio.h> 

#define LED 25
#define SIO_BASE 0xd0000000
#define REG_GPIO_OE_SET (SIO_BASE + 0x024) // Output enable set
#define PAD_CONTROL_BASE 0x4001c000 
#define REG_PAD_CONTROL_GPIO25 (PAD_CONTROL_BASE + 0x6c) // Pad control for GPIO25
#define BANK0_BASE 0x40014000 
#define REG_GPIO25_CTRL (BANK0_BASE + 0x0cc) // GPIO25 control
#define REG_GPIO_OE_SET (SIO_BASE + 0x024)
#define REG_GPIO_OUT_SET (SIO_BASE + 0x014)
#define REG_GPIO_OUT_CLR (SIO_BASE + 0x018)

#define CONTENT_OF(addr) (*(volatile uint32_t *)(addr))

int main(void) {
  // TODO - Initialise components and variables
    const uint32_t led_mask = 0x1 << LED;
    const uint32_t FUNC_SIO = 5;
    CONTENT_OF(REG_PAD_CONTROL_GPIO25) = (CONTENT_OF(REG_PAD_CONTROL_GPIO25)) & ~ ( 1<<7 | 1<<6); 
    CONTENT_OF(REG_GPIO25_CTRL) = FUNC_SIO; 
    CONTENT_OF(REG_GPIO_OE_SET) = led_mask; 

  while (true) {
    // TODO - Repeated code here
    CONTENT_OF(REG_GPIO_OUT_SET) = led_mask; // Set the LED on

    for (uint32_t i = 0; i < 8000000; i++) { // Delay loop
      __asm volatile("nop");
    }

    CONTENT_OF(REG_GPIO_OUT_CLR) = led_mask; // Set the LED off

    for (uint32_t i = 0; i < 8000000; i++) { // Delay loop
      __asm volatile("nop");
    }
  }
}

