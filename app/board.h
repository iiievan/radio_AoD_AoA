#ifndef __BOARD_H
#define __BOARD_H

#include "utils.h"

#define PIN_DISCONNECTED         0xFFFFFFFF    // Define that pin is disconnected from hardware

#if defined(NRF52833_XXAA)  // плата аудиогида на контроллере nrf52840/nrf52833
    #define PORT_0  0
    #define PORT_1  BIT(5)
    
    // дефайны используемые в коде но не используемые на плате аудиогида
    // подтяг к несуществующему порту
    #define BUTTON_UP_PIN           PIN_DISCONNECTED
    #define BUTTON_DOWN_PIN         PIN_DISCONNECTED
    #define SYS_1V8_PIN             PIN_DISCONNECTED
    #define RF_SWANT_PIN            PIN_DISCONNECTED  // подтянут к +3.0V


    #define LED_GREEN_PIN           (PORT_0 | 7)   //P0.07
    #define BAT_LED_1_PIN           (PORT_0 | 8)   //P0.08
    #define BAT_LED_2_PIN           (PORT_0 | 6)   //P0.06
    #define BAT_LED_3_PIN           (PORT_0 | 4)   //P0.04
    #define BAT_LED_4_PIN           (PORT_0 | 27)  //P0.27
    #define BAT_LED_5_PIN           (PORT_0 | 5)   //P0.05
    #define LED_KEYBOARD_PIN        (PORT_0 | 25)  //P0.25     // светодиод подсветки клавиатуры
    #define LED_PLPA_BTN_PIN        (PORT_0 | 11)  //P0.11     // светодиод подсветки кнопки play/pause
    #define LED_VOL_BTN_PIN         (PORT_0 | 26)  //P0.26     // светодиод подсветки кнопки громкости
    #define LED_RED_PIN             LED_GREEN_PIN

    #define I2S_MCK_PIN             (PORT_0 | 18)  // P0.18 MAX_MCLK
    #define I2S_LRCK_PIN            (PORT_0 | 20)  // P0.20 I2S_LRCLK
    #define I2S_SCK_PIN             (PORT_0 | 17)  // P0.17 I2S_CLK
    #define I2S_SDIN_PIN            (PORT_0 | 22)  // P0. I2S_SDIN
    #define I2S_SDOUT_PIN           (PORT_0 | 19)  // P0. I2S_SDOUT
            
    #define I2C_CLCK_PIN            (PORT_0 | 16)  // P0.16
    #define I2C_SDA_PIN             (PORT_0 | 15)  // P0.15
            
    #define RF_MODE_PIN             (PORT_1 | 6)   // P0.06    
    #define RF_RX_EN_PIN            (PORT_0 | 9)   // P0.09
    #define RF_TX_EN_PIN            (PORT_0 | 10)  // P0.10
    #define RF_PDET_PIN             (PORT_0 | 2)   // P0.02
    
    #define CURRENT_INCREASE_PIN_1  (PORT_0 | 28)  // P0.28 MAIN_MEAS
    #define CURRENT_INCREASE_PIN_2  (PORT_0 | 29)  // P0.29 VBAT_MEAS   
    #define CHRG_EN_PIN             (PORT_0 | 3)   // P0.03 CHPRG/PWKEY
    #define RF_POWER_ENABLE         (PORT_1 | 14)  // P1.14 3V0_RF_EN
    #define MODULE_PWR              (PORT_1 | 8)   // P1.08 GSM and GPS power enable
    #define JACK_5_PIN              (PORT_0 | 30)  // P0.30
    #define JACK_6_PIN              (PORT_0 | 31)  // P0.31
    #define SYS_3V0_PIN             (PORT_1 | 7)   // P1.07
    #define GSM_PWR_PIN              MODULE_PWR
    #define ACC_PWR_PIN              SYS_3V0_PIN

    //#define BUZZER                  (PORT_0 | 4)   // P0.04 BUZZER
    #define VIBRO                   (PORT_1 | 12)  // P1.12 VIBRO
    
    #define GPS_UART_RX             (PORT_1 | 9)   // P1.09
    #define GPS_UART_TX             (PORT_0 | 12)  // P0.12
    #define GSM_UART_RX             (PORT_0 | 13)  // P0.13
    #define GSM_UART_TX             (PORT_0 | 14)  // P0.14
    #define UART_RX_PIN             GSM_UART_RX             
    #define UART_TX_PIN             GSM_UART_TX
        
    // matrix keypad definitions
    #define BTN_ROW_1               (PORT_1 | 11)   // P1.11
    #define BTN_ROW_2               (PORT_1 | 4)    // P1.04
    #define BTN_ROW_3               (PORT_1 | 3)    // P1.03
    #define BTN_ROW_4               (PORT_1 | 2)    // P1.02
    #define BTN_ROW_5               (PORT_1 | 1)    // P1.01
    #define BTN_ROW_6               (PORT_1 | 13)   // P1.13
                                                        
    #define BTN_COL_1               (PORT_1 | 15)   // P1.15
    #define BTN_COL_2               (PORT_1 | 10)   // P1.10
    #define BTN_COL_3               (PORT_1 | 5)    // P1.05

#elif defined(SMALL_MARK_CR2032)

  #define BUTTON_UP_PIN           25
  #define LED_GREEN_PIN           26
  #define LED_RED_PIN             26

  #define RF_TX()
  #define RF_RX()
  #define RF_OFF()
  #define RF_BYPASS()

  #define LED_R_ON        nrf_gpio_pin_set(LED_RED_PIN)
  #define LED_R_OFF       nrf_gpio_pin_clear(LED_RED_PIN)
  #define LED_G_ON        nrf_gpio_pin_set(LED_GREEN_PIN)
  #define LED_G_OFF       nrf_gpio_pin_clear(LED_GREEN_PIN)

#elif defined(HW_GSM)

  //номера пинов МК
  #define LED_RED_PIN             21
  #define LED_GREEN_PIN           20
  #define BAT_LED_1_PIN           8  
  #define BAT_LED_2_PIN           7
  #define BAT_LED_3_PIN           6
  #define BAT_LED_4_PIN           1
  #define BAT_LED_5_PIN           0
  #define LED_VOL_BTN_PIN         11

  #define RF_MODE_PIN             22
  #define RF_SWANT_PIN            RF_MODE_PIN
  #define RF_RX_EN_PIN            23
  #define RF_TX_EN_PIN            24
  #define RF_PDET_PIN             28

  #define I2C_CLCK_PIN            10
  #define I2C_SDA_PIN             9
  #define SYS_1V8_PIN             19
  #define SYS_3V0_PIN             19

  //GSM_IGN+CHRG
  #define CHRG_EN_PIN             29
  
  #define I2S_MCK_PIN             14
  #define I2S_LRCK_PIN            16
  #define I2S_SCK_PIN             15
  #define I2S_SDIN_PIN            18
  #define I2S_SDOUT_PIN           17

  #define BUTTON_UP_PIN           27
  #define BUTTON_DOWN_PIN         25

  #define JACK_5_PIN              5
  #define JACK_6_PIN              4

  #define RF_POWER_ENABLE         26

  #define UART_RX_PIN             12              
  #define UART_TX_PIN             13
  #define ACC_PWR_PIN             30
  #define GSM_PWR_PIN             31

#elif defined(NRF52811_XXAA)

  //номера пинов МК
  #define LED_GREEN_PIN           21
  #define LED_RED_PIN             LED_GREEN_PIN
  #define BAT_LED_1_PIN           14  
  #define BAT_LED_2_PIN           15
  #define BAT_LED_3_PIN           16
  #define BAT_LED_4_PIN           17
  #define BAT_LED_5_PIN           18
  #define LED_VOL_BTN_PIN         12

  #define RF_MODE_PIN             22
  #define RF_RX_EN_PIN            23
  #define RF_TX_EN_PIN            24
  #define RF_PDET_PIN             31
  #define RF_SWANT_PIN            PIN_DISCONNECTED

  #define I2C_CLCK_PIN            8
  #define I2C_SDA_PIN             9
  #define SYS_1V8_PIN             PIN_DISCONNECTED
  #define SYS_3V0_PIN             10

  #define CHRG_EN_PIN             4

  #define I2S_MCK_PIN             7
  #define I2S_LRCK_PIN            1
  #define I2S_SCK_PIN             6
  #define I2S_SDIN_PIN            2
  #define I2S_SDOUT_PIN           0

  #define BUTTON_UP_PIN           29
  #define BUTTON_DOWN_PIN         30

  #define JACK_5_PIN              28
  #define JACK_6_PIN              PIN_DISCONNECTED

  #define RF_POWER_ENABLE         11

  #define CMT_SPI_SO              27
  #define CMT_SPI_SI              25
  #define CMT_SPI_SCK             26
  #define CMT_SPI_CS              13

  #define CMT_NIRQ                20
  #define SD_SPI_CS               19

#else

  //логический список светодиодов
  #define RED_LED                 0
  #define GREEN_LED               1
  #define BAT_1_LED               2
  #define BAT_2_LED               3
  #define BAT_3_LED               4
  #define BAT_4_LED               5
  #define BAT_5_LED               6
  #define BTN_LED                 7
  #define LED_NUM                 8

  //номера пинов МК
  #define LED_RED_PIN             21
  #define LED_GREEN_PIN           20
  #define BAT_LED_1_PIN           13   
  #define BAT_LED_2_PIN           14
  #define BAT_LED_3_PIN           15
  #define BAT_LED_4_PIN           16
  #define BAT_LED_5_PIN           17
  #define LED_VOL_BTN_PIN         12

  #define RF_MODE_PIN             22
  #define RF_SWANT_PIN            25
  #define RF_RX_EN_PIN            23
  #define RF_TX_EN_PIN            24
  #define RF_PDET_PIN             28

  #define I2C_CLCK_PIN            8
  #define I2C_SDA_PIN             9
  #define SYS_1V8_PIN             11
  #define SYS_3V0_PIN             10

  #define CHRG_EN_PIN             4

  #define I2S_MCK_PIN             7
  #define I2S_LRCK_PIN            2
  #define I2S_SCK_PIN             6
  #define I2S_SDIN_PIN            0
  #define I2S_SDOUT_PIN           1

  #define BUTTON_UP_PIN           26
  #define BUTTON_DOWN_PIN         31

  #define JACK_4_PIN              29
  #define JACK_5_PIN              30

  #define RF_POWER_ENABLE         27
#endif

#ifndef SMALL_MARK_CR2032

  typedef enum {
    CHRG_MAX_CURRENT,
    CHRG_MEDIUM_CURRENT,
    CHRG_MIN_CURRENT,
  }ECHRG_TYPE;

  #define LED_R_ON        nrf_gpio_cfg_input(LED_RED_PIN, NRF_GPIO_PIN_PULLUP)
  #define LED_R_OFF       nrf_gpio_cfg_input(LED_RED_PIN, NRF_GPIO_PIN_PULLDOWN)
  #define LED_G_ON        nrf_gpio_cfg_input(LED_GREEN_PIN, NRF_GPIO_PIN_PULLUP)
  #define LED_G_OFF       nrf_gpio_cfg_input(LED_GREEN_PIN, NRF_GPIO_PIN_PULLDOWN)

  extern void RF_OFF();
  extern void RF_RX();
  extern void rf_pwr_on();
  extern void rf_pwr_off();
#endif
  
extern void Delay100us(u32 Dly);
extern void Delay10us(u32 Dly);
extern void Delay1us(u32 Dly);

extern u16 CRC16( const u8 *pBuf, u32 uiLength );
extern u16 CRC16_FILL(const u8 *pBuf, u32 uiLength, u16 fill);
extern void InitGPIO(void);
extern void clock_initialization();
extern void nrf_drv_common_irq_enable(IRQn_Type IRQn, uint8_t priority);
extern void Reset();

#endif //__BOARD_H