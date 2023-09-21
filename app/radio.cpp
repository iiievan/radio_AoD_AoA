#include "radio.h"
#include "intrinsics.h"

NRF_Radio::NRF_Radio(n_RADIO_regs::NRF_RADIO_Type *p_radio_regs, uint8_t main, uint8_t second)
: s_REGS(*p_radio_regs), m_main_chnl(main), m_second_chnl(second), m_base_addr(0xFF)
{
    this->state = n_RADIO_regs::RADIO_DISABLED;
}

void  NRF_Radio::init_rx(n_RADIO_regs::e_TXPOWER power, uint8_t ch_num)
{ 
    s_REGS.POWER.b.POWER = 1;                               //Peripheral is powered on
    s_REGS.TXPOWER.b.TXPOWER = power;    

    s_REGS.PACKETPTR.reg = (uint32_t)&m_rx_buffer[0];
    s_REGS.MODE.b.MODE   = n_RADIO_regs::Nrf_1Mbit;
    s_REGS.TXADDRESS.b.TXADDRESS = 0x0;
    s_REGS.RXADDRESSES.b.ADDR = BIT(0);
    
    s_REGS.FREQUENCY.b.FREQUENCY = get_frequency(ch_num);
    
    // Packet configuration
    s_REGS.PCNF0.b.S1LEN = PACKET_S1_FIELD_SIZE;        // 0
    s_REGS.PCNF0.b.S0LEN = PACKET_S0_FIELD_SIZE;        // 0    
    s_REGS.PCNF0.b.LFLEN = PACKET_LENGTH_FIELD_SIZE;    // 0
    s_REGS.PCNF0.b.PLEN  = n_RADIO_regs::PLEN_16BIT;
      
    s_REGS.PCNF1.b.WHITEEN = HIGH; 
    s_REGS.PCNF1.b.ENDIAN  = n_RADIO_regs::LITTLE_ENDIAN;
    s_REGS.PCNF1.b.BALEN   = PACKET_BASE_ADDRESS_LENGTH;
    s_REGS.PCNF1.b.STATLEN = PACKET_STATIC_LENGTH;
    s_REGS.PCNF1.b.MAXLEN  = PACKET_STATIC_LENGTH;
    
    // CRC Config
    s_REGS.CRCCNF.b.LEN = 1; // len 1 byte;
    s_REGS.CRCINIT.b.CRCINIT = 0xFF;
    s_REGS.CRCPOLY.b.CRCPOLY = 0x107;
  
    //default whitening
    s_REGS.DATAWHITEIV.b.DATAWHITEIV = 0x40;
            
    set_address(ch_num);
  
    // shortcuts for Radio
    s_REGS.SHORTS.b.ADDRESS_RSSISTART = HIGH;   // short event ADDRESS and task RSSISTART
    s_REGS.SHORTS.b.DISABLED_RSSISTOP = HIGH;   // short event DISABLED and task RSSISTOP
    s_REGS.SHORTS.b.END_DISABLE       = HIGH;   // short event END and task DISABLE
    
    // interrupts for radio
    s_REGS.INTENSET.b.CRCOK = HIGH;   // enable interrupt for event CRCOK
    s_REGS.INTENSET.b.END   = HIGH;   // enable interrupt for event END 
    s_REGS.INTENSET.b.READY = HIGH;   // enable interrupt for event READY
    
    NVIC_SetPriority(RADIO_IRQn, RADIO_RX_INT_PRIORITY);
    NVIC_ClearPendingIRQ(RADIO_IRQn);
    NVIC_EnableIRQ(RADIO_IRQn);
}

void  NRF_Radio::init_tx(n_RADIO_regs::e_TXPOWER power, uint8_t ch_num)
{ 
    s_REGS.POWER.b.POWER = 1;                               //Peripheral is powered on
    s_REGS.TXPOWER.b.TXPOWER = power;
    
    s_REGS.PACKETPTR.reg = (uint32_t)&m_tx_buffer[0];
    s_REGS.MODE.b.MODE   = n_RADIO_regs::Nrf_1Mbit;
    s_REGS.TXADDRESS.b.TXADDRESS = 0x0;
    s_REGS.RXADDRESSES.b.ADDR = BIT(0);
      
    s_REGS.FREQUENCY.b.FREQUENCY = get_frequency(ch_num);
    
    // Packet configuration
    s_REGS.PCNF0.b.S1LEN = PACKET_S1_FIELD_SIZE;        // 0
    s_REGS.PCNF0.b.S0LEN = PACKET_S0_FIELD_SIZE;        // 0    
    s_REGS.PCNF0.b.LFLEN = PACKET_LENGTH_FIELD_SIZE;    // 0
    s_REGS.PCNF0.b.PLEN  = n_RADIO_regs::PLEN_16BIT;
      
    s_REGS.PCNF1.b.WHITEEN = HIGH; 
    s_REGS.PCNF1.b.ENDIAN  = n_RADIO_regs::LITTLE_ENDIAN;
    s_REGS.PCNF1.b.BALEN   = PACKET_BASE_ADDRESS_LENGTH;
    s_REGS.PCNF1.b.STATLEN = PACKET_STATIC_LENGTH;
    s_REGS.PCNF1.b.MAXLEN  = PACKET_STATIC_LENGTH;
    
    // CRC Config
    s_REGS.CRCCNF.b.LEN = 1; // len 1 byte;
    s_REGS.CRCINIT.b.CRCINIT = 0xFF;
    s_REGS.CRCPOLY.b.CRCPOLY = 0x107;
  
    //default whitening
    s_REGS.DATAWHITEIV.b.DATAWHITEIV = 0x40;
            
    set_address(ch_num);
  
    // shortcuts for Radio
    s_REGS.SHORTS.b.ADDRESS_RSSISTART = HIGH;   // short event ADDRESS and task RSSISTART
    s_REGS.SHORTS.b.DISABLED_RSSISTOP = HIGH;   // short event DISABLED and task RSSISTOP
    s_REGS.SHORTS.b.END_DISABLE       = HIGH;   // short event END and task DISABLE
    
    // interrupts for radio
    s_REGS.INTENSET.b.CRCOK = HIGH;   // enable interrupt for event CRCOK
    s_REGS.INTENSET.b.END   = HIGH;   // enable interrupt for event END 
    s_REGS.INTENSET.b.READY = HIGH;   // enable interrupt for event READY
    
    NVIC_SetPriority(RADIO_IRQn, RADIO_RX_INT_PRIORITY);
    NVIC_ClearPendingIRQ(RADIO_IRQn);
    NVIC_EnableIRQ(RADIO_IRQn);
}

uint8_t NRF_Radio::get_frequency(uint8_t ch)
{
    uint8_t freq;

    // Special cases for BT advertise channels 
    if (ch == 37)
        freq = 2;
    else if (ch == 38)
        freq = 26;
    else if (ch == 39)
        freq = 80;
    else
        freq = 2*ch + (ch < 11 ? 4 : 6);

    return freq;
}

void  NRF_Radio::set_address(uint8_t ch_num)
{  
    m_main_chnl = ch_num;
  
    //адрес для передачи звука
    switch (m_base_addr)
    {
      case 1:
          s_REGS.BASE0.reg = 0xB2CA5600;
          break;
      case 2:
          s_REGS.BASE0.reg = 0xB4CA5600;
          break;
      case 3:
          s_REGS.BASE0.reg = 0xB5CA5600;
          break;
      case 4: 
          s_REGS.BASE0.reg = 0xB8CA5600;
          break;
      case 0xff:
      default:
          s_REGS.BASE0.reg = 0xB1CA5600;
          break;
    }
  
    m_set_prefix(ch_num);
  
    //адрес для ble(0x8e) и служебного канала (0xAA)
    s_REGS.PREFIX1.b.AP    = 0x0000AA8E;
    s_REGS.BASE1.b.BASE1   = 0x89BED600;
}

void  NRF_Radio::m_set_prefix(uint8_t ch_num)
{
    uint32_t prfx = (ch_num + 10) & 0xFF;
  
    s_REGS.PREFIX0.b.AP = prfx;
}

void  NRF_Radio::tx()
{
  
}

void  NRF_Radio::rx()
{
  
}

void  NRF_Radio::off()
{
  
}

void  NRF_Radio::audio_link_Q()
{
  
}

void RADIO_IRQHandler()
{
    if (NRF_RADIO->EVENTS_CRCOK)
    {
        __disable_interrupt();
  
        NRF_RADIO->EVENTS_CRCOK = 0;
  
        __enable_interrupt(); 
    }
  
    if (NRF_RADIO->EVENTS_END)
    {
        NRF_RADIO->EVENTS_END = 0;
    }

    if (NRF_RADIO->EVENTS_READY)
    {
        NRF_RADIO->EVENTS_READY = 0;  
  
        NRF_RADIO->TASKS_START = 1U;
    }
}

NRF_Radio radio(n_RADIO_regs::MAIN_RADIO_regs,1,44);
