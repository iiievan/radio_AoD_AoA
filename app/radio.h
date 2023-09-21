#ifndef __RADIO_H_
#define __RADIO_H_

#include "n_RADIO_regs.h"

#define LNA_GAIN_DB  (14)
#define RADIO_RX_INT_PRIORITY   (4)

#define PACKET_S1_FIELD_SIZE        (0UL)   // Packet S1 field size in bits. 
#define PACKET_S0_FIELD_SIZE        (0UL)   // Packet S0 field size in bits. 
#define PACKET_LENGTH_FIELD_SIZE    (0UL)   // Packet length field size in bits. 
#define PACKET_BASE_ADDRESS_LENGTH  (3UL)   // Packet base address length field size in bytes
#define PACKET_STATIC_LENGTH        (20UL)  // Packet static length in bytes

typedef union 
{ 
    struct 
    {  
        uint8_t    RESERVED     :5;     // bit: 1..5
        uint8_t    CP           :1;     // bit: 6        (RW). положение зависит канал ли это данных(CTEINLINECONF.CTEINFOINS1 = InS1) или advertising(CTEINLINECONF.CTEINFOINS1 = NotInS1)
        uint8_t    RESRVED1     :2;     // bit: 7,8                
    } data;     //InS1                  // Structure used for bit access
    struct 
    {  
        uint8_t    PDU_type     :4;     // bit: 1..4    (RW) ƒл€ PDU рекламного канала флаг CTEInfo замен€ет бит CP( расположен в PAYLOAD)
        uint8_t    RESRVED      :4;     // bit: 5..8                
    } adv;      //NotInS1               // Structure used for bit access 
    uint8_t  S0;                        // Type used for whole union acces
} S0_t;

typedef union 
{ 
    struct 
    {  
        uint8_t    CTETime     :5;     // bit: 1..5     (RW).field defines the length of the CTE in 8 µs units. May by change by DFECTRL1.NUMBEROF8US or CTEINLINECONF.CTETIMEVALIDRANGE.
        uint8_t    RFU         :1;     // bit: 6        (RW).
        uint8_t    CTEType     :2;     // bit: 7,8      (RW). [see e_CTEType]             
    } CTE;                             // Structure used for bit access
    uint8_t  S1;                       // Type used for whole union acces
} CTEInfo_t;

enum e_CTEType : uint8_t
{
    AoA       = 0x0,     // AoA, no switching
    AoD_1us   = 0x1,     // AoD, 1us slots
    AoD_2us   = 0x2,      // AoD, 2us slots
    CTE_RESERVED = 0x03  // Reserved for future use.
};

typedef __packed struct 
{
    uint8_t   ADDRESS[6];    // first 48(6 bytes) bits of the payload are the device address
       S0_t   S0;            //  
    uint8_t   LENGHT;
  CTEInfo_t   S1;            // CTEInfo присутстует если установлен бит CP в S0, другими словами adv это пакет или data
    uint8_t  *PAYLOAD;
   uint16_t   CRC;
   uint32_t   CTE_packet;   // пакет дл€ AoD и AoA, режим AoA или AoD определ€етс€ в DFEMODE 
} RF_packet_t;

class NRF_Radio
{
    n_RADIO_regs::e_RADIO_STATE  state;     //see n_RADIO_regs::STATE_reg_t
                         int8_t  RSSI;      //RSSISAMPLE reg

public:
          NRF_Radio(n_RADIO_regs::NRF_RADIO_Type *p_radio_regs, uint8_t main, uint8_t second);
         ~NRF_Radio() {}

    void  init_rx(n_RADIO_regs::e_TXPOWER power, uint8_t ch_num);
    void  init_tx(n_RADIO_regs::e_TXPOWER power, uint8_t ch_num);
 uint8_t  get_frequency(uint8_t ch);
    void  set_address(uint8_t ch_num);    

    void  tx();
    void  rx();
    void  off();

    void  audio_link_Q();
    
private:
  
    void  m_set_prefix(uint8_t ch_num);
    
    n_RADIO_regs::NRF_RADIO_Type &s_REGS;
    
                         uint8_t  m_main_chnl;
                         uint8_t  m_second_chnl;                         
                         uint8_t  m_base_addr;
                         
                         uint8_t  m_rx_buffer[PACKET_STATIC_LENGTH];
                         uint8_t  m_tx_buffer[PACKET_STATIC_LENGTH];                         
};

extern "C" void RADIO_IRQHandler();
extern NRF_Radio radio;

#endif // __RADIO_H