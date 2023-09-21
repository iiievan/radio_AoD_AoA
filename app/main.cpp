#include <stdio.h>
#include "nrf.h"
#include "nrf_gpio.h"
#include "board.h"
#include "n_RADIO_regs.h"

void InitGPIO();

int main()
{
  InitGPIO();
  return 0;
}

void InitGPIO()
{  
  const uint32_t RADIO_size = sizeof(n_RADIO_regs::NRF_RADIO_Type);
  
  //LEDS
  nrf_gpio_cfg_input(BAT_LED_1_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_2_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_3_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_4_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(BAT_LED_5_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(LED_RED_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(LED_GREEN_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(LED_VOL_BTN_PIN, NRF_GPIO_PIN_PULLDOWN);
#ifdef NRF52833_XXAA
  nrf_gpio_cfg_input(LED_PLPA_BTN_PIN, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_input(LED_KEYBOARD_PIN, NRF_GPIO_PIN_PULLDOWN);
#endif
}