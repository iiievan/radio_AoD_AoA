#include "nrf.h"
#include "utils.h"

namespace n_RADIO_regs
{
    typedef union 
    { 
        struct 
        {             
            uint32_t    T     :1;     // bit: 0        (W) Trigger write HIGH to it.   
            uint32_t          :31;    // bit: 1..32    RESERVED
        } b;                          // Structure used for bit access 
        uint32_t  reg;                // Type used for register access 
    } TASKS_reg_t;
      
    typedef union 
    { 
        struct 
        {             
            uint32_t    G  :1;          // bit: 0        (RW) Event Generated or notGenerated  [see e_EVENT_G] 
            uint32_t       :31;         // bit: 1..32    RESERVED
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } EVENTS_reg_t;
    
    enum e_EVENT_G
    {
        EVENT_NOTGENERATED = 0x0,       // Event not generated
        EVENT_GENERATED = 0x1,          // Event generated
    };

    typedef union 
    { 
        struct 
        {             
            uint32_t    READY_START        :1;  // bit: 0(A)        (RW) Shortcut between event READY and task START        [ see e_DISENABLE ]
            uint32_t    END_DISABLE        :1;  // bit: 1(B)        (RW) Shortcut between event END and task DISABLE        [ see e_DISENABLE ]
            uint32_t    DISABLED_TXEN      :1;  // bit: 2(C)        (RW) Shortcut between event DISABLED and task TXEN      [ see e_DISENABLE ]
            uint32_t    DISABLED_RXEN      :1;  // bit: 3(D)        (RW) Shortcut between event DISABLED and task RXEN      [ see e_DISENABLE ]
            uint32_t    ADDRESS_RSSISTART  :1;  // bit: 4(E)        (RW) Shortcut between event ADDRESS and task RSSISTART  [ see e_DISENABLE ]
            uint32_t    END_START          :1;  // bit: 5(F)        (RW) Shortcut between event END and task START          [ see e_DISENABLE ]
            uint32_t    ADDRESS_BCSTART    :1;  // bit: 6(G)        (RW) Shortcut between event ADDRESS and task BCSTART    [ see e_DISENABLE ]
            uint32_t                       :1;  // bit: 7           RESERVED 
            uint32_t    DISABLED_RSSISTOP  :1;  // bit: 8(H)        (RW) Shortcut between event DISABLED and task RSSISTOP  [ see e_DISENABLE ]
            uint32_t                       :2;  // bit: 9,10        RESERVED 
            uint32_t    RXREADY_CCASTART   :1;  // bit: 11(K)       (RW) Shortcut between event RXREADY and task CCASTART   [ see e_DISENABLE ]
            uint32_t    CCAIDLE_TXEN       :1;  // bit: 12(L)       (RW) Shortcut between event CCAIDLE and task TXEN       [ see e_DISENABLE ]
            uint32_t    CCABUSY_DISABLE    :1;  // bit: 13(M)       (RW) Shortcut between event CCABUSY and task DISABLE    [ see e_DISENABLE ]
            uint32_t    FRAMESTART_BCSTART :1;  // bit: 14(N)       (RW) Shortcut between event FRAMESTART and task BCSTART [ see e_DISENABLE ]
            uint32_t    READY_EDSTART      :1;  // bit: 15(O)       (RW) Shortcut between event READY and task EDSTART      [ see e_DISENABLE ]
            uint32_t    EDEND_DISABLE      :1;  // bit: 16(P)       (RW) Shortcut between event EDEND and task DISABLE      [ see e_DISENABLE ]
            uint32_t    CCAIDLE_STOP       :1;  // bit: 17(Q)       (RW) Shortcut between event CCAIDLE and task STOP       [ see e_DISENABLE ]
            uint32_t    TXREADY_START      :1;  // bit: 18(R)       (RW) Shortcut between event TXREADY and task START      [ see e_DISENABLE ]
            uint32_t    RXREADY_START      :1;  // bit: 19(S)       (RW) Shortcut between event RXREADY and task START      [ see e_DISENABLE ]
            uint32_t    PHYEND_DISABLE     :1;  // bit: 20(T)       (RW) Shortcut between event PHYEND and task DISABLE     [ see e_DISENABLE ]
            uint32_t    PHYEND_START       :1;  // bit: 21(U)       (RW) Shortcut between event PHYEND and task START       [ see e_DISENABLE ]
            uint32_t                       :10; // bit: 22..32      RESERVED
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } SHORTS_reg_t; 

    typedef union 
    { 
        struct 
        {             
            uint32_t    READY       :1;  // bit: 0(A)        (RW) Write '1' to enable interrupt for event READY         [ see e_DISENABLE ]
            uint32_t    ADDRESS     :1;  // bit: 1(B)        (RW) Write '1' to enable interrupt for event ADDRESS       [ see e_DISENABLE ]
            uint32_t    PAYLOAD     :1;  // bit: 2(C)        (RW) Write '1' to enable interrupt for event PAYLOAD       [ see e_DISENABLE ]
            uint32_t    END         :1;  // bit: 3(D)        (RW) Write '1' to enable interrupt for event END           [ see e_DISENABLE ]
            uint32_t    DISABLED    :1;  // bit: 4(E)        (RW) Write '1' to enable interrupt for event DISABLED      [ see e_DISENABLE ]
            uint32_t    DEVMATCH    :1;  // bit: 5(F)        (RW) Write '1' to enable interrupt for event DEVMATCH      [ see e_DISENABLE ]
            uint32_t    DEVMISS     :1;  // bit: 6(G)        (RW) Write '1' to enable interrupt for event DEVMISS       [ see e_DISENABLE ]            
            uint32_t    RSSIEND     :1;  // bit: 7(H)        (RW) Write '1' to enable interrupt for event RSSIEND       [ see e_DISENABLE ]
                                         //                       A new RSSI sample is ready for readout from the RADIO.RSSISAMPLE register  
            uint32_t                :2;  // bit: 8,9         RESERVED 
            uint32_t    BCMATCH     :1;  // bit: 10(I)       (RW) Write '1' to enable interrupt for event BCMATCH
                                         //                       Bit counter value is specified in the RADIO.BCC register   [ see e_DISENABLE ]
            uint32_t                :1;  // bit: 11          RESERVED
            uint32_t    CRCOK       :1;  // bit: 12(K)       (RW) Write '1' to enable interrupt for event CRCOK         [ see e_DISENABLE ]
            uint32_t    CRCERROR    :1;  // bit: 13(L)       (RW) Write '1' to enable interrupt for event CRCERROR      [ see e_DISENABLE ]
            uint32_t    FRAMESTART  :1;  // bit: 14(M)       (RW) Write '1' to enable interrupt for event FRAMESTART    [ see e_DISENABLE ]
            uint32_t    EDEND       :1;  // bit: 15(N)       (RW) Write '1' to enable interrupt for event EDEND         [ see e_DISENABLE ]
            uint32_t    EDSTOPPED   :1;  // bit: 16(O)       (RW) Write '1' to enable interrupt for event EDSTOPPED     [ see e_DISENABLE ]
            uint32_t    CCAIDLE     :1;  // bit: 17(P)       (RW) Write '1' to enable interrupt for event CCAIDLE       [ see e_DISENABLE ]
            uint32_t    CCABUSY     :1;  // bit: 18(Q)       (RW) Write '1' to enable interrupt for event CCABUSY       [ see e_DISENABLE ]
            uint32_t    CCASTOPPED  :1;  // bit: 19(R)       (RW) Write '1' to enable interrupt for event CCASTOPPED    [ see e_DISENABLE ]
            uint32_t    RATEBOOST   :1;  // bit: 20(S)       (RW) Write '1' to enable interrupt for event RATEBOOST     [ see e_DISENABLE ]
            uint32_t    TXREADY     :1;  // bit: 21(T)       (RW) Write '1' to enable interrupt for event TXREADY       [ see e_DISENABLE ]
            uint32_t    RXREADY     :1;  // bit: 22(U)       (RW) Write '1' to enable interrupt for event RXREADY       [ see e_DISENABLE ]
            uint32_t    MHRMATCH    :1;  // bit: 23(V)       (RW) Write '1' to enable interrupt for event MHRMATCH      [ see e_DISENABLE ]
            uint32_t                :2;  // bit: 24,25       RESERVED 
            uint32_t    SYNC        :1;  // bit: 26(Y)       (RW) Write '1' to enable interrupt for event SYNC
                                         //                       A possible preamble has been received in Ble_LR125Kbit, Ble_LR500Kbit, 
                                         //                       or Ieee802154_250Kbit modes during an RX transaction. 
                                         //                       False triggering of the event is possible.            [ see e_DISENABLE ]
            uint32_t    PHYEND      :1;  // bit: 27(Z)       (RW) Write '1' to enable interrupt for event PHYEND        [ see e_DISENABLE ]
            uint32_t    CTEPRESENT  :1;  // bit: 28(a)       (RW) Write '1' to enable interrupt for event CTEPRESENT    [ see e_DISENABLE ]
            uint32_t                :3;  // bit: 29..32      RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } INTENSET_reg_t; 
    
    typedef union 
    { 
        struct 
        {             
            uint32_t    READY       :1;  // bit: 0(A)        (RW) Write '1' to disable  interrupt for event READY         [ see e_DISENABLE ]
            uint32_t    ADDRESS     :1;  // bit: 1(B)        (RW) Write '1' to disable  interrupt for event ADDRESS       [ see e_DISENABLE ]
            uint32_t    PAYLOAD     :1;  // bit: 2(C)        (RW) Write '1' to disable  interrupt for event PAYLOAD       [ see e_DISENABLE ]
            uint32_t    END         :1;  // bit: 3(D)        (RW) Write '1' to disable  interrupt for event END           [ see e_DISENABLE ]
            uint32_t    DISABLED    :1;  // bit: 4(E)        (RW) Write '1' to disable  interrupt for event DISABLED      [ see e_DISENABLE ]
            uint32_t    DEVMATCH    :1;  // bit: 5(F)        (RW) Write '1' to disable  interrupt for event DEVMATCH      [ see e_DISENABLE ]
            uint32_t    DEVMISS     :1;  // bit: 6(G)        (RW) Write '1' to disable  interrupt for event DEVMISS       [ see e_DISENABLE ]            
            uint32_t    RSSIEND     :1;  // bit: 7(H)        (RW) Write '1' to disable  interrupt for event RSSIEND       [ see e_DISENABLE ]
                                         //                       A new RSSI sample is ready for readout from the RADIO.RSSISAMPLE register  
            uint32_t                :2;  // bit: 8,9         RESERVED 
            uint32_t    BCMATCH     :1;  // bit: 10(I)       (RW) Write '1' to disable interrupt for event BCMATCH
                                         //                       Bit counter value is specified in the RADIO.BCC register   [ see e_DISENABLE ]
            uint32_t                :1;  // bit: 11          RESERVED
            uint32_t    CRCOK       :1;  // bit: 12(K)       (RW) Write '1' to disable interrupt for event CRCOK         [ see e_DISENABLE ]
            uint32_t    CRCERROR    :1;  // bit: 13(L)       (RW) Write '1' to disable interrupt for event CRCERROR      [ see e_DISENABLE ]
            uint32_t    FRAMESTART  :1;  // bit: 14(M)       (RW) Write '1' to disable interrupt for event FRAMESTART    [ see e_DISENABLE ]
            uint32_t    EDEND       :1;  // bit: 15(N)       (RW) Write '1' to disable interrupt for event EDEND         [ see e_DISENABLE ]
            uint32_t    EDSTOPPED   :1;  // bit: 16(O)       (RW) Write '1' to disable interrupt for event EDSTOPPED     [ see e_DISENABLE ]
            uint32_t    CCAIDLE     :1;  // bit: 17(P)       (RW) Write '1' to disable interrupt for event CCAIDLE       [ see e_DISENABLE ]
            uint32_t    CCABUSY     :1;  // bit: 18(Q)       (RW) Write '1' to disable interrupt for event CCABUSY       [ see e_DISENABLE ]
            uint32_t    CCASTOPPED  :1;  // bit: 19(R)       (RW) Write '1' to disable interrupt for event CCASTOPPED    [ see e_DISENABLE ]
            uint32_t    RATEBOOST   :1;  // bit: 20(S)       (RW) Write '1' to disable interrupt for event RATEBOOST     [ see e_DISENABLE ]
            uint32_t    TXREADY     :1;  // bit: 21(T)       (RW) Write '1' to disable interrupt for event TXREADY       [ see e_DISENABLE ]
            uint32_t    RXREADY     :1;  // bit: 22(U)       (RW) Write '1' to disable interrupt for event RXREADY       [ see e_DISENABLE ]
            uint32_t    MHRMATCH    :1;  // bit: 23(V)       (RW) Write '1' to disable interrupt for event MHRMATCH      [ see e_DISENABLE ]
            uint32_t                :2;  // bit: 24,25       RESERVED 
            uint32_t    SYNC        :1;  // bit: 26(Y)       (RW) Write '1' to disable interrupt for event SYNC
                                         //                       A possible preamble has been received in Ble_LR125Kbit, Ble_LR500Kbit, 
                                         //                       or Ieee802154_250Kbit modes during an RX transaction. 
                                         //                       False triggering of the event is possible.            [ see e_DISENABLE ]
            uint32_t    PHYEND      :1;  // bit: 27(Z)       (RW) Write '1' to disable interrupt for event PHYEND        [ see e_DISENABLE ]
            uint32_t    CTEPRESENT  :1;  // bit: 28(a)       (RW) Write '1' to disable interrupt for event CTEPRESENT    [ see e_DISENABLE ]
            uint32_t                :3;  // bit: 29..32      RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } INTENCLR_reg_t;
    
    enum e_INTEN_flags: uint32_t
    {
        F_INTEN_READY       = BIT(0),
        F_INTEN_ADDRESS     = BIT(1),
        F_INTEN_PAYLOAD     = BIT(2),
        F_INTEN_END         = BIT(3),
        F_INTEN_DISABLED    = BIT(4),
        F_INTEN_DEVMATCH    = BIT(5),
        F_INTEN_DEVMISS     = BIT(6),
        F_INTEN_RSSIEND     = BIT(7),
        F_INTEN_BCMATCH     = BIT(10),
        F_INTEN_CRCOK       = BIT(12),
        F_INTEN_CRCERROR    = BIT(13),
        F_INTEN_FRAMESTART  = BIT(14),
        F_INTEN_EDEND       = BIT(15),
        F_INTEN_EDSTOPPED   = BIT(16),
        F_INTEN_CCAIDLE     = BIT(17),
        F_INTEN_CCABUSY     = BIT(18),
        F_INTEN_CCASTOPPED  = BIT(19),
        F_INTEN_RATEBOOST   = BIT(20),
        F_INTEN_TXREADY     = BIT(21),
        F_INTEN_RXREADY     = BIT(22),
        F_INTEN_MHRMATCH    = BIT(23),
        F_INTEN_SYNC        = BIT(26),
        F_INTEN_PHYEND      = BIT(27),
        F_INTEN_CTEPRESENT  = BIT(28),
        F_INTEN_ALL      = 0x1CFFF4FF
    };
    
    enum e_DISENABLE
    {
        DISABLED = 0x0,       
        ENABLED  = 0x1      
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  CRCSTATUS  :1;    // bit: 0        (R) CRC status of packet received  [0x0 = Packet received with CRC error; 0x1 = Packet received with CRC ok] 
            uint32_t             :31;   // bit: 1..32    RESERVED
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } CRCSTATUS_reg_t; 
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  RXMATCH  :3;      // bit: 0..2       (R) Logical address of which previous packet was received
            uint32_t           :29;     // bit: 3..32      RESERVED
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } RXMATCH_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t RXCRC     :24;      // bit: 0..23       (R) CRC field of previously received packet
            uint32_t           :8;       // bit: 24..32      RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } RXCRC_reg_t;   
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  DAI      :3;      // bit: 0..2       (R) Device address match index
                                        //                     Index (n) of device address, see DAB[n] and DAP[n], 
                                        //                     that got an address match.
            uint32_t           :29;     // bit: 3..32      RESERVED
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } DAI_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  PDUSTAT  :1;      // bit: 0       (R) Status on payload length vs. PCNF1.MAXLEN [see e_PDUSTAT]
            uint32_t  CISTAT   :2;      // bit: 1,2     (R) Status on what rate packet is received with in Long Range [see e_CISTAT]
            uint32_t           :29;     // bit: 3..32      RESERVED
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } PDUSTAT_reg_t;
    
    enum e_PDUSTAT
    {
        LessThan_MAXLEN     = 0x0,  //  Payload less than PCNF1.MAXLEN    
        GreaterThan_MAXLEN  = 0x1   //  Payload greater than PCNF1.MAXLEN     
    };
    
    enum e_CISTAT
    {
        LR125kbit  = 0x0,   // Frame is received at 125 kbps     
        LR500kbit  = 0x1    // Frame is received at 500 kbps    
    };

    typedef union 
    { 
        struct 
        {             
            uint32_t  CTETIME   :5;      // bit: 0..4  (R) CTETime parsed from packet
            uint32_t  RFU       :1;      // bit: 5     (R) RFU parsed from packet
            uint32_t  CTETYPE   :2;      // bit: 2     (R) CTEType parsed from packet
            uint32_t            :24;     // bit: 3..32      RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } CTESTATUS_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  SWITCHINGSTATE  :3;      // bit: 0..2   (R) Internal state of switching state machine [see e_SWITCHINGSTATE]
            uint32_t                  :1;      // bit: 3      RESERVED
            uint32_t  SAMPLINGSTATE   :1;      // bit: 4      (R) Internal state of sampling state machine [see e_SAMPLINGSTATE]
            uint32_t                  :27;     // bit: 5..32  RESERVED
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } DFESTATUS_reg_t;
    
    enum e_SWITCHINGSTATE
    {
        SW_IDLE        = 0x0,   // Switching state Idle     
        SW_OFFSET      = 0x1,    // Switching state Offset
        SW_GUARD       = 0x2,   // Switching state Guard     
        SW_REF         = 0x3,    // Switching state Ref
        SW_SWITCHING   = 0x4,   // Switching state Switching     
        SW_ENDING      = 0x5    // Switching state Ending
    }; 
    
    enum e_SAMPLINGSTATE
    {
        SAMP_IDLE      = 0x0,   // Sampling state Idle     
        SAMP_SAMPLING  = 0x1    // Sampling state Sampling    
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  PACKETPTR      :32;     // bit: 0..32  (RW) Packet pointer.
                                              //             Packet address to be used for the next transmission or reception. 
                                              //             When transmitting, the packet pointed to by this address will be 
                                              //             transmitted and when receiving, the received packet will be written to this address. 
                                              //             This address is a byte aligned RAM address. See the memory chapter 
                                              //             for details about which memories are avilable for EasyDMA.
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } PACKETPTR_reg_t;   
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  FREQUENCY     :7;      // bit: 0..6    (RW) Radio channel frequency [0..100]
                                             //                   Frequency = 2400 + FREQUENCY (MHz)
            uint32_t                :1;      // bit: 7       RESERVED
            uint32_t  MAP           :1;      // bit: 8       (RW) Channel map selection [see e_FREQMAP ]
            uint32_t                :23;     // bit: 9..32      RESERVED
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } FREQUENCY_reg_t;  
    
    
    enum e_FREQMAP
    {
        MAP_DEFAULT = 0x0, // Channel map between 2400 MHZ .. 2500 MHz; Frequency = 2400 + FREQUENCY (MHz) 
        MAP_LOW = 0x1      // Channel map between 2360 MHZ .. 2460 MHz ;Frequency = 2360 + FREQUENCY (MHz)
    };
   
    typedef union 
    { 
        struct 
        {             
            uint32_t  TXPOWER   :8;      // bit: 0..7       (RW) RADIO output power
                                         //                 Output power in number of dBm, i.e. if the value -20 
                                         //                 is specified the output power will be set to -20 dBm. [ see e_TXPOWER]
            uint32_t            :24;     // bit: 8..32      RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } TXPOWER_reg_t;
    
    enum e_TXPOWER
    {
        PWR_0dBm        = 0x0,  // 0 dBm
        PWR_Pos3dBm     = 0x3,  // +3 dBm
        PWR_Pos4dBm     = 0x4,  // +4 dBm
        PWR_Neg40dBm    = 0xD8, // -40 dBm
        PWR_Neg30dBm    = 0xE2, // -30 dBm
        PWR_Neg20dBm    = 0xEC, // -20 dBm
        PWR_Neg16dBm    = 0xF0, // -16 dBm
        PWR_Neg12dBm    = 0xF4, // -12 dBm
        PWR_Neg8dBm     = 0xF8, // -8 dBm
        PWR_Neg4dBm     = 0xFC, // -4 dBm
    };
 
    typedef union 
    { 
        struct 
        {             
            uint32_t  MODE      :4;      // bit: 0..3       (RW) Radio data rate and modulation setting. 
                                         //                 The radio supports frequency-shift keying (FSK) modulation. [see e_RADIO_MODES]
            uint32_t            :28;     // bit: 4..32      RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } MODE_reg_t;

    enum e_RADIO_MODES
    {
        Nrf_1Mbit            = 0x0,  // 1 Mbps Nordic proprietary radio mode
        Nrf_2Mbit            = 0x1,  // 2 Mbps Nordic proprietary radio mode
        Ble_1Mbit            = 0x3,  // 1 Mbps BLE
        Ble_2Mbit            = 0x4,  // 2 Mbps BLE
        Ble_LR125Kbit        = 0x5,  // Long range 125 kbps TX, 125 kbps and 500 kbps RX
        Ble_LR500Kbit        = 0x6,  // Long range 500 kbps TX, 125 kbps and 500 kbps RX
        Ieee802154_250Kbit   = 0x15  // IEEE 802.15.4-2006 250 kbps
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  LFLEN      :4;     // bit: 0..3       (RW) Length on air of LENGTH field in number of bits.
            uint32_t             :4;     // bit: 4..7       RESERVED
            uint32_t  S0LEN      :1;     // bit: 8          (RW) Length on air of S0 field in number of bytes 
            uint32_t             :7;     // bit: 9..15      RESERVED 
            uint32_t  S1LEN      :4;     // bit: 16..19     (RW) Length on air of S1 field in number of bits 
            uint32_t  S1INCL     :1;     // bit: 20         (RW) Include or exclude S1 field in RAM [see e_S1INCL] 
            uint32_t             :1;     // bit: 21         RESERVED
            uint32_t  CILEN      :2;     // bit: 22,23      (RW) Length of code indicator - long range 
            uint32_t  PLEN       :2;     // bit: 24,25      (RW) Length of preamble on air. Decision point: TASKS_START task [see e_PLEN]
            uint32_t  CRCINC     :1;     // bit: 26         (RW) Indicates if LENGTH field contains CRC or not [e_CRCINC] 
            uint32_t             :2;     // bit: 27,28      RESERVED
            uint32_t  TERMLEN    :2;     // bit: 29,30      (RW) Length of TERM field in Long Range operation 
            uint32_t             :1;     // bit: 31         RESERVED
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } PCNF0_reg_t;
    
    enum e_S1INCL
    {
        S1_AUTOMATIC = 0x0,   // Include S1 field in RAM only if S1LEN > 0
        S1_INCLUDE   = 0x1    // Always include S1 field in RAM independent of S1LEN
    };
    
    enum e_PLEN
    {
        PLEN_8BIT       = 0x0,  // 8-bit preamble
        PLEN_16BIT      = 0x1,  // 16-bit preamble
        PLEN_32BITZERO  = 0x2,  // 32-bit zero preamble - used for IEEE 802.15.4
        PLEN_LONGRANGE  = 0x3   // Preamble - used for BLE long range
    };
    
    enum e_CRCINC
    {
        CRC_EXCLUDE = 0x0,  // LENGTH does not contain CRC
        CRC_INCLUDE = 0x1   // LENGTH includes CRC
    };
    
     typedef union 
    { 
        struct 
        {             
            uint32_t  MAXLEN      :8;     // bit: 0..7       (RW) Maximum length of packet payload. If the packet payload is larger than MAXLEN, 
                                          //                      the radio will truncate the payload to MAXLEN. [0..255]
            uint32_t  STATLEN     :8;     // bit: 8..15      (RW) Static length in number of bytes
                                          //                      The static length parameter is added to the total length of the payload 
                                          //                      when sending and receiving packets, e.g. if the static length is set to N the 
                                          //                      radio will receive or send N bytes more than what is defined in the LENGTH field of the packet. 
            uint32_t  BALEN       :3;     // bit: 16..18     (RW) Base address length in number of bytes
                                          //                      The address field is composed of the base address and the one byte long address prefix, 
                                          //                      e.g. set BALEN=2 to get a total address of 3 bytes. [0..4]
            uint32_t              :5;     // bit: 19..23     RESERVED 
            uint32_t  ENDIAN      :1;     // bit: 24         (RW) On-air endianness of packet, this applies to the S0, LENGTH, S1, and the PAYLOAD fields. [see e_ENDIAN] 
            uint32_t  WHITEEN     :1;     // bit: 25         (RW) Enable or disable packet whitening [0x0 = Disable; 0x1 = Enable]
            uint32_t              :6;     // bit: 26..31     RESERVED
         } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } PCNF1_reg_t; 
    
    enum e_ENDIAN
    {
      LITTLE_ENDIAN = 0x0,  // Least significant bit on air first
      BIG_ENDIAN    = 0x1   // Most significant bit on air first
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  BASE0    :32;      // bit: 0..32  (RW) Base address 0 
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } BASE0_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  BASE1    :32;      // bit: 0..32  (RW) Base address 1 
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } BASE1_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  AP;         // bit: 0..32  (RW) Address prefix i. Prefixes bytes for logical addresses 0-3
        } b;                     // Structure used for bit access 
        uint32_t  reg;           // Type used for register access 
    } PREFIX0_reg_t; 
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  AP;        // bit: 0..32  (RW) Address prefix i. Prefixes bytes for logical addresses 4-7
        } b;                     // Structure used for bit access 
        uint32_t  reg;           // Type used for register access 
    } PREFIX1_reg_t;
  
    typedef union 
    { 
        struct 
        {             
            uint32_t  TXADDRESS  :3;       // bit: 0..2   (RW) Transmit address select. Logical address to be used when transmitting a packet.
            uint32_t             :29;      // bit: 3..32  RESERVED
        } b;                               // Structure used for bit access 
        uint32_t  reg;                     // Type used for register access 
    } TXADDRESS_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  ADDR  :8;       // bit: 0..7   (RW) Enable or disable reception on logical address i.[see e_RXADDR_flags]
            uint32_t        :24;      // bit: 8..32  RESERVED
        } b;                          // Structure used for bit access 
        uint32_t  reg;                // Type used for register access 
    } RXADDRESSES_reg_t;   
    
    enum e_RXADDR_flags: uint32_t
    {
        F_RXADDR_A     = BIT(0),    // [0x0 = Disable; 0x1 = Enable] on logical address 0
        F_RXADDR_B     = BIT(1),    // [0x0 = Disable; 0x1 = Enable] on logical address 1
        F_RXADDR_C     = BIT(2),    // [0x0 = Disable; 0x1 = Enable] on logical address 2
        F_RXADDR_D     = BIT(3),    // [0x0 = Disable; 0x1 = Enable] on logical address 3
        F_RXADDR_E     = BIT(4),    // [0x0 = Disable; 0x1 = Enable] on logical address 4
        F_RXADDR_F     = BIT(5),    // [0x0 = Disable; 0x1 = Enable] on logical address 5
        F_RXADDR_G     = BIT(6),    // [0x0 = Disable; 0x1 = Enable] on logical address 6
        F_RXADDR_H     = BIT(7),    // [0x0 = Disable; 0x1 = Enable] on logical address 7     
        F_RXADDR_ALL   = 0xFF
    };    
 
    typedef union 
    { 
        struct 
        {             
            uint32_t  LEN        :2;       // bit: 0,1      (RW) CRC length in number of bytes For MODE Ble_LR125Kbit and Ble_LR500Kbit, 
                                           //                    only LEN set to 3 is supported [1..3] 0x0 - Disabled
            uint32_t             :6;       // bit: 2..7     RESERVED
            uint32_t  SKIPADDR   :2;       // bit: 8,9      (RW) Include or exclude packet address field out of CRC calculation.[see e_SKIPADDR]
            uint32_t             :22;      // bit: 10..32   RESERVED
        } b;                               // Structure used for bit access 
        uint32_t  reg;                     // Type used for register access 
    } CRCCNF_reg_t; 
    
    enum e_SKIPADDR
    {
        INCLUDE_CRC = 0x0,  // CRC calculation includes address field
        SKIP_CRC    = 0x1,  // CRC calculation does not include address field. The CRC calculation will start at the first byte after the address.
        IEEE802154  = 0x2   // CRC calculation as per 802.15.4 standard. Starting at first byte after length field.        
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  CRCPOLY    :24;     // bit: 0..23    (RW) CRC polynomial. Each term in the CRC polynomial is mapped to a bit in this register which index corresponds to the term's exponent. 
                                          //                    The least significant term/bit is hardwired internally to 1, and bit number 0 of the register content is ignored by the hardware. 
                                          //                    The following example is for an 8 bit CRC polynomial: x8 + x7 + x3 + x2 + 1 = 1 1000 1101 .
            uint32_t             :8;      // bit: 23..32   RESERVED
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access 
    } CRCPOLY_reg_t;    
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  CRCINIT    :24;     // bit: 0..23    (RW) CRC initial value.Initial value for CRC calculation
            uint32_t             :8;      // bit: 23..32   RESERVED
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access 
    } CRCINIT_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  TIFS    :10;     // bit: 0..9    (RW) Interframe spacing in 탎.
                                       //                   Interframe space is the time interval between two consecutive packets. 
                                       //                   It is defined as the time, in microseconds, from the end of the last bit of 
                                       //                   the previous packet to the start of the first bit of the subsequent packet.
            uint32_t          :22;     // bit: 10..32   RESERVED
        } b;                           // Structure used for bit access 
        uint32_t  reg;                 // Type used for register access 
    } TIFS_reg_t;

    typedef union 
    { 
        struct 
        {             
            uint32_t  RSSISAMPLE    :7;     // bit: 0..6    (R) RSSI sample.[0..127]
                                            //                  RSSI sample result. The value of this register is read as a positive value while the actual
                                            //                  received signal strength is a negative value. Actual received signal strength is therefore 
                                            //                  as follows: received signal strength = -A dBm.
            uint32_t                :25;    // bit: 7..32   RESERVED
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } RSSISAMPLE_reg_t;  

    typedef union 
    { 
        struct 
        {             
            uint32_t  STATE    :4;      // bit: 0..3    (R) Current radio state [see e_RADIO_STATE]
            uint32_t           :28;     // bit: 4..32   RESERVED
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } STATE_reg_t;
    
    enum e_RADIO_STATE
    {
        RADIO_DISABLED  = 0x0,  // RADIO is in the Disabled state
        RADIO_RXRU      = 0x1,  // RADIO is in the RXRU state
        RADIO_RXIDLE    = 0x2,  // RADIO is in the RXIDLE state
        RADIO_RX        = 0x3,  // RADIO is in the RX state
        RADIO_RXDISABLE = 0x4,  // RADIO is in the RXDISABLED state
        RADIO_TXRU      = 0x9,  // RADIO is in the TXRU state
        RADIO_TXIDLE    = 0x10, // RADIO is in the TXIDLE state
        RADIO_TX        = 0x11, // RADIO is in the TX state
        RADIO_TXDISABLE = 0x12, // RADIO is in the TXDISABLED state
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  DATAWHITEIV    :7;      // bit: 0..6    (RW) Data whitening initial value. Bit 6 is hardwired to '1', 
                                              //                  writing '0' to it has no effect, and it will always be read back and used by the device as '1'.
                                              //                  Bit 0 corresponds to Position 6 of the LSFR, Bit 1 to Position 5, etc.
            uint32_t                 :25;     // bit: 7..32   RESERVED
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } DATAWHITEIV_reg_t;  
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  BCC    :32;      // bit: 0..32    (RW) Bit counter compare register.
        } b;                           // Structure used for bit access 
        uint32_t  reg;                 // Type used for register access 
    } BCC_reg_t; 
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  DAB    :32;      // bit: 0..32    (RW) Device address base segment n.(n = 0..7) 
                                       //                    Address offset: 0x620 + (n ? 0x4)
        } b;                           // Structure used for bit access 
        uint32_t  reg;                 // Type used for register access 
    } DAB_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  DAP    :16;      // bit: 0..15    (RW) Device address prefix n.(n = 0..7) 
                                       //                    Address offset: 0x620 + (n ? 0x4)
            uint32_t         :16;      // bit: 16..32   RESERVED
            
        } b;                           // Structure used for bit access 
        uint32_t  reg;                 // Type used for register access 
    } DAP_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  ENA      :8;    // bit: 0..7     (RW) Enable or disable device address matching using device address i [see e_DAENA_flags]
            uint32_t  TXADD    :8;    // bit: 8..15    (RW) TxAdd for device address i [see e_DATXADD_flags]
            uint32_t           :16;   // bit: 16..32   RESERVED
            
        } b;                          // Structure used for bit access 
        uint32_t  reg;                // Type used for register access 
    } DACNF_reg_t;
    
    enum e_DAENA_flags: uint32_t
    {
        F_DAENA_A     = BIT(0),    // [0x0 = Disable; 0x1 = Enable] on address 0
        F_DAENA_B     = BIT(1),    // [0x0 = Disable; 0x1 = Enable] on address 1
        F_DAENA_C     = BIT(2),    // [0x0 = Disable; 0x1 = Enable] on address 2
        F_DAENA_D     = BIT(3),    // [0x0 = Disable; 0x1 = Enable] on address 3
        F_DAENA_E     = BIT(4),    // [0x0 = Disable; 0x1 = Enable] on address 4
        F_DAENA_F     = BIT(5),    // [0x0 = Disable; 0x1 = Enable] on address 5
        F_DAENA_G     = BIT(6),    // [0x0 = Disable; 0x1 = Enable] on address 6
        F_DAENA_H     = BIT(7),    // [0x0 = Disable; 0x1 = Enable] on address 7     
        F_DAENA_ALL   = 0xFF
    }; 
    
    enum e_DATXADD_flags: uint32_t
    {
        F_DATXADD_A     = BIT(0),    // [0x0 = Disable; 0x1 = Enable] on address 0
        F_DATXADD_B     = BIT(1),    // [0x0 = Disable; 0x1 = Enable] on address 1
        F_DATXADD_C     = BIT(2),    // [0x0 = Disable; 0x1 = Enable] on address 2
        F_DATXADD_D     = BIT(3),    // [0x0 = Disable; 0x1 = Enable] on address 3
        F_DATXADD_E     = BIT(4),    // [0x0 = Disable; 0x1 = Enable] on address 4
        F_DATXADD_F     = BIT(5),    // [0x0 = Disable; 0x1 = Enable] on address 5
        F_DATXADD_G     = BIT(6),    // [0x0 = Disable; 0x1 = Enable] on address 6
        F_DATXADD_H     = BIT(7),    // [0x0 = Disable; 0x1 = Enable] on address 7     
        F_DATXADD_ALL   = 0xFF
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  MHRMATCHCONF      :32;    // bit: 0..32     (RW) Search pattern configuration            
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } MHRMATCHCONF_reg_t;

    typedef union 
    { 
        struct 
        {             
            uint32_t  MHRMATCHMAS      :32;    // bit: 0..32     (RW) Pattern mask            
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } MHRMATCHMAS_reg_t;  
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  RU      :1;    // bit: 0     (RW) Radio ramp-up time.
                                     //             0x0 = Default ramp-up time (tRXEN and tTXEN), compatible with firmware written for nRF51,
                                     //             0x1 = Fast ramp-up (tRXEN,FAST and tTXEN,FAST), see electrical specifications for more information
                                     //                   When enabled, TIFS is not enforced by hardware and software needs to control when to turn on the Radio
            uint32_t          :7;    // bit: 1..7   RESERVED 
            uint32_t  DTX     :2;    // bit: 8,9    (RW) Default TX value
                                     //                  Specifies what the RADIO will transmit when it is not started, i.e. between:
                                     //                  RADIO.EVENTS_READY and RADIO.TASKS_START
                                     //                  RADIO.EVENTS_END and RADIO.TASKS_START
                                     //                  RADIO.EVENTS_END and RADIO.EVENTS_DISABLED
                                     //                  For IEEE 802.15.4 250 kbps mode only Center is a valid setting
                                     //                  For Bluetooth Low Energy Long Range mode only Center is a valid setting
                                     //                  0x0 = B1  - Transmit '1'
                                     //                  0x1 = B0, - Transmit '0'
                                     //                  0x2 = Center - When tuning the crystal for center frequency, the RADIO must be set in 
                                     //                        DTX = Center mode to be able to achieve the expected accuracy
           uint32_t           :22;   // bit: 10..32   RESERVED
        } b;                         // Structure used for bit access 
        uint32_t  reg;               // Type used for register access 
    } MODECNF0_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  SFD      :8;    // bit: 0..7   (RW) IEEE 802.15.4 start of frame delimiter
            uint32_t           :24;   // bit: 8..32   RESERVED 
        } b;                          // Structure used for bit access 
        uint32_t  reg;                // Type used for register access 
    } SFD_reg_t;    
 
    typedef union 
    { 
        struct 
        {             
            uint32_t  EDCNT    :21;    // bit: 0..20   (RW) IEEE 802.15.4 energy detect loop count
                                       // Number of iterations to perform an ED scan. If set to 0 one scan is performed, 
                                       // otherwise the specified number + 1 of ED scans will be performed and the max ED value tracked in EDSAMPLE.
            uint32_t           :11;    // bit: 21..31   RESERVED 
        } b;                           // Structure used for bit access 
        uint32_t  reg;                 // Type used for register access 
    } EDCNT_reg_t;
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  EDLVL     :8;     // bit: 0..7   (RW) IEEE 802.15.4 energy detect level [0..127]
                                        // Register value must be converted to IEEE 802.15.4 range by an 8-bit 
                                        // saturating multiplication by factor ED_RSSISCALE, as shown in the code example for ED sampling
            uint32_t            :24;    // bit: 8..32   RESERVED 
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access 
    } EDSAMPLE_reg_t; 
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  CCAMODE       :3;    // bit: 0..2    (RW) CCA mode of operation [see e_CCAEDTHRES]
            uint32_t                :5;    // bit: 3..7    RESERVED
            uint32_t  CCAEDTHRES    :8;    // bit: 8..15   (RW) CCA energy busy threshold. Used in all the CCA modes except CarrierMode.
                                           //                   Must be converted from IEEE 802.15.4 range by dividing by factor ED_RSSISCALE 
                                           //                  - similar to EDSAMPLE register [see e_CCAEDTHRES]
            uint32_t  CCACORRTHRES  :8;    // bit: 16..23  (RW) CCA correlator busy threshold. Only relevant to CarrierMode, CarrierAndEdMode, and CarrierOrEdMode.
            uint32_t  CCACORRCNT    :8;    // bit: 24..31  (RW) Limit for occurances above CCACORRTHRES. When not equal to zero the corrolator based signal detect is enabled.
        } b;                               // Structure used for bit access 
        uint32_t  reg;                     // Type used for register access 
    } CCACTRL_reg_t;
    
    enum e_CCAEDTHRES
    {
        CCA_EDMODE           = 0x0, // Energy above threshold Will report busy whenever energy is detected above CCAEDTHRES
        CCA_CARRIERMODE      = 0x1, // Carrier seen Will report busy whenever compliant IEEE 802.15.4 signal is seen
        CCA_CARRIERandEDMODE = 0x2, // Energy above threshold AND carrier seen
        CCA_CARRIERorEDMODE  = 0x3, // Energy above threshold OR carrier seen
        CCA_EDMODETest1      = 0x4  // Energy above threshold test mode that will abort when first ED measurement over threshold is seen. No averaging.      
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  DFEOPMODE     :2;     // bit: 0,1   (RW) Direction finding operation mode [see e_DFEMODE]
            uint32_t                :30;    // bit: 2..32 RESERVED 
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } DFEMODE_reg_t;
    
    enum e_DFEMODE
    {
        DFE_DISABLED = 0x0,     // Direction finding mode disabled
        DFE_AoD      = 0x2,     // Direction finding mode set to AoD
        DFE_AoA      = 0x3      // Direction finding mode set to AoA      
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  CTEINLINECTRLEN       :1;     // bit: 0         (RW) Enable parsing of CTEInfo from received packet in BLE modes
                                                    //                     0x0 = Disabled - Parsing of CTEInfo is enabled
                                                    //                     0x1 = Enabled - Parsing of CTEInfo is disabled
            uint32_t                        :2;     // bit: 1,2       RESERVED
            uint32_t  CTEINFOINS1           :1;     // bit: 3         (RW) CTEInfo is S1 byte or not
                                                    //                     0x0 = CTEInfo is NOT in S1 byte (advertising PDU)
                                                    //                     0x1 = CTEInfo is in S1 byte (data PDU)
            uint32_t  CTEERRORHANDLING      :1;     // bit: 4         (RW) Sampling/switching if CRC is not OK
                                                    //                     0x0 = No sampling and antenna switching when CRC is not OK
                                                    //                     0x1 = Sampling and antenna switching also when CRC is not OK
            uint32_t                        :1;     // bit: 5         RESERVED
            uint32_t  CTETIMEVALIDRANGE     :2;     // bit: 6,7       (RW) Max range of CTETime
                                                    //                     Valid range is 2-20 in BLE core spec. If larger than 20, it 
                                                    //                     can be an indication of an error in the received packet.
                                                    //                     0x0 = 20 in 8 탎 unit (default). Set to 20 if parsed CTETime is larger than 20
                                                    //                     0x1 = 31 in 8 탎 unit
                                                    //                     0x2 = 63 in 8 탎 unit
            uint32_t                        :2;     // bit: 8,9       RESERVED
            uint32_t  CTEINLINERXMODE1US    :3;     // bit: 10..12    (RW) Spacing between samples for the samples in the SWITCHING period when CTEINLINEMODE is set.
                                                    //                     When the device is in AoD mode, this is used when the received CTEType is "AoD 1 탎". 
                                                    //                     When in AoA mode, this is used when TSWITCHSPACING is 2 탎. [see e_SAMPINTERVAL]
            uint32_t  CTEINLINERXMODE2US    :3;     // bit: 13..15    (RW) Spacing between samples for the samples in the SWITCHING period when CTEINLINEMODE is set.
                                                    //                     When the device is in AoD mode, this is used when the received CTEType is "AoD 2 탎". 
                                                    //                     When in AoA mode, this is used when TSWITCHSPACING is 4 탎.[see e_SAMPINTERVAL]
            uint32_t  S0CONF                :8;     // bit: 16..23    (RW) S0 bit pattern to match
                                                    //                     The least significant bit always corresponds to the first bit of S0 received.
            uint32_t  S0MASK                :8;     // bit: 24..31    (RW) S0 bit mask to set which bit to match
                                                    //                     The least significant bit always corresponds to the first bit of S0 received.
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } CTEINLINECONF_reg_t;

    typedef union 
    { 
        struct 
        {             
            uint32_t  NUMBEROF8US        :6;     // bit: 0..5      (RW) Length of the AoA/AoD procedure in number of 8 탎 units
                                                 //                     Always used in TX mode, but in RX mode only when CTEINLINECTRLEN is 0
            uint32_t                     :1;     // bit: 6         RESERVED
            uint32_t  DFEINEXTENSION     :1;     // bit: 7         (RW) Add CTE extension and do antenna switching/sampling in this extension
                                                 //                0x0 = Payload - Antenna switching/sampling is done in the packet payload
                                                 //                0x1 = CRC - AoA/AoD procedure triggered at end of CRC
            uint32_t  TSWITCHSPACING     :3;     // bit: 8..10     (RW) Interval between every time the antenna is changed in the SWITCHING state
                                                 //                0x1 = 4 탎
                                                 //                0x2 = 2 탎
                                                 //                0x3 = 1 us
            uint32_t                     :1;     // bit: 11        RESERVED
            uint32_t  TSAMPLESPACINGREF  :3;     // bit: 12..14    (RW) Interval between samples in the REFERENCE period [see e_SAMPINTERVAL]          
            uint32_t  SAMPLETYPE         :1;     // bit: 15        (RW) Whether to sample I/Q or magnitude/phase
                                                 //                0x0 = Complex samples in I and Q
                                                 //                0x1 = Complex samples as magnitude and phase
            uint32_t  TSAMPLESPACING     :3;     // bit: 16..18    (RW) Interval between samples in the SWITCHING period when CTEINLINECTRLEN is 0
                                                 //                     Not used when CTEINLINECTRLEN is set. Then either CTEINLINERXMODE1US or 
                                                 //                     CTEINLINERXMODE2US are used.[see e_SAMPINTERVAL] 
            uint32_t                     :5;     // bit: 19..23    RESERVED
            uint32_t  AGCBACKOFFGAIN     :4;     // bit: 24..27    (RW) Gain will be lowered by the specified number of gain steps at the start of CTE
                                                 //                     First LNAGAIN gain drops, then MIXGAIN, then AAFGAIN
            uint32_t                     :4;     // bit: 28..31    RESERVED

        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } DFECTRL1_reg_t;    
    
    enum e_SAMPINTERVAL
    {
        CTE_4US     = 0x1,  // 4 탎
        CTE_2US     = 0x2,  // 2 탎
        CTE_1US     = 0x3,  // 1 탎
        CTE_500NS   = 0x4,  // 0.5 탎
        CTE_250NS   = 0x5,  // 0.25 탎
        CTE_125NS   = 0x6,  // 0.125 탎        
    };
    
    typedef union 
    { 
        struct 
        {             
            uint32_t  TSWITCHOFFSET     :13;   // bit: 0..12   (RW) Signed value offset after the end of the CRC before starting switching in number of 16M cycles
                                               //                   Decreasing TSWITCHOFFSET beyond the trigger of the AoA/AoD procedure will have no effect
            uint32_t                    :3;    // bit: 13..15  RESERVED
            uint32_t  TSAMPLEOFFSET     :12;   // bit: 16..27  (RW) Signed value offset before starting sampling in number of 16M cycles relative to the beginning of 
                                               //                   the REFERENCE state - 12 탎 after switching start
                                               //                   Decreasing TSAMPLEOFFSET beyond the trigger of the AoA/AoD procedure will have no effect
            uint32_t                    :4;    // bit: 28..31  RESERVED 
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } DFECTRL2_reg_t;
    
    typedef union 
    { 
        // GPIO patterns to be used for each antenna
        // Maximum 8 GPIOs can be controlled. To secure correct signal levels on the pins, the pins must be configured 
        // in the GPIO peripheral as described in Pin configuration.
        // If, during switching, the total number of antenna slots is bigger than the number of written patterns, 
        // the RADIO loops back to the pattern used after the reference pattern.
        // A minimum number of three patterns must be written.      
        struct 
        {             
            uint32_t  SWITCHPATTERN     :8;    // bit: 0..7   (RW) Fill array of GPIO patterns for antenna control.
                                               //                  The GPIO pattern array size is 40 entries.
                                               //                  When written, bit n corresponds to the GPIO configured in PSEL.DFEGPIO[n].
                                               //                  When read, returns the number of GPIO patterns written since the last time the array was 
                                               //                  cleared. Use CLEARPATTERN to clear the array.
            uint32_t                    :24;   // bit: 8..31  RESERVED 
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } SWITCHPATTERN_reg_t;   
    
    typedef union 
    {     
        struct 
        {             
            uint32_t  CLEARPATTERN     :1;    // bit: 0      (RW) Clears GPIO pattern array for antenna control. 0x1 - Clear
            uint32_t                   :31;   // bit: 1..31  RESERVED 
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } CLEARPATTERN_reg_t;    
    
    typedef union 
    {     
        struct 
        {             
            uint32_t  PIN         :5;    // bit: 0      (RW) Pin number [0..31]
            uint32_t              :26;   // bit: 1..30  RESERVED 
            uint32_t  CONNECT     :1;    // bit: 31     (RW) Connection
                                         //                  0x0 - Connected
                                         //                  0x1 - Disconnected            
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } DFEGPIO_reg_t; 
    
    //@brief RADIO_PSEL [PSEL] (Unspecified)
    typedef struct 
    {
        __IOM DFEGPIO_reg_t  DFEGPIO[8];            // (0x00000000) Description collection: Pin select for DFE pin
                                                    //              n                                                        
    } RADIO_PSEL_reg_t;                             //!< Size = 32 (0x20)                                                          


    //@brief RADIO_DFEPACKET [DFEPACKET] (DFE packet EasyDMA channel)  
    typedef struct 
    {
        __IOM uint32_t  PTR;                    // (@ 0x00000000) Data pointer                                               
        __IOM uint32_t  MAXCNT;                 // (@ 0x00000004) Maximum number of buffer words to transfer                 
        __IM  uint32_t  AMOUNT;                 // (@ 0x00000008) Number of samples transferred in the last transaction      
    } RADIO_DFEPACKET_reg_t;                    // Size = 12 (0xc) 
    
    typedef union 
    {     
        struct 
        {             
            uint32_t  POWER       :1;    // bit: 0      (RW) Peripheral power control. The peripheral and its registers 
                                         //                  will be reset to its initial state by switching the peripheral off and then back on again.
                                         //                  0x0 = Peripheral is powered off
                                         //                  0x1 = Peripheral is powered on
            uint32_t              :31;   // bit: 1..31  RESERVED           
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } POWER_reg_t;    

    struct NRF_RADIO_Type
    {                                                   // (0x40001000) RADIO Structure                                            
        __OM  TASKS_reg_t           TASKS_TXEN;         // (0x00000000) Enable RADIO in TX mode                                    
        __OM  TASKS_reg_t           TASKS_RXEN;         // (0x00000004) Enable RADIO in RX mode                                    
        __OM  TASKS_reg_t           TASKS_START;        // (0x00000008) Start RADIO                                                
        __OM  TASKS_reg_t           TASKS_STOP;         // (0x0000000C) Stop RADIO                                                 
        __OM  TASKS_reg_t           TASKS_DISABLE;      // (0x00000010) Disable RADIO                                              
        __OM  TASKS_reg_t           TASKS_RSSISTART;    // (0x00000014) Start the RSSI and take one single sample of
                                                        //              the receive signal strength                               
        __OM  TASKS_reg_t           TASKS_RSSISTOP;     // (0x00000018) Stop the RSSI measurement                                  
        __OM  TASKS_reg_t           TASKS_BCSTART;      // (0x0000001C) Start the bit counter                                      
        __OM  TASKS_reg_t           TASKS_BCSTOP;       // (0x00000020) Stop the bit counter                                       
        __OM  TASKS_reg_t           TASKS_EDSTART;      // (0x00000024) Start the energy detect measurement used in IEEE
                                                        //              802.15.4 mode                                              
        __OM  TASKS_reg_t           TASKS_EDSTOP;       // (0x00000028) Stop the energy detect measurement                         
        __OM  TASKS_reg_t           TASKS_CCASTART;     // (0x0000002C) Start the clear channel assessment used in IEEE
                                                        //              802.15.4 mode                                             
        __OM  TASKS_reg_t           TASKS_CCASTOP;      // (0x00000030) Stop the clear channel assessment                          
        __IM  uint32_t              RESERVED[51];       
        __IOM EVENTS_reg_t          EVENTS_READY;       // (0x00000100) RADIO has ramped up and is ready to be started             
        __IOM EVENTS_reg_t          EVENTS_ADDRESS;     // (0x00000104) Address sent or received                                   
        __IOM EVENTS_reg_t          EVENTS_PAYLOAD;     // (0x00000108) Packet payload sent or received                            
        __IOM EVENTS_reg_t          EVENTS_END;         // (0x0000010C) Packet sent or received                                    
        __IOM EVENTS_reg_t          EVENTS_DISABLED;    // (0x00000110) RADIO has been disabled                                    
        __IOM EVENTS_reg_t          EVENTS_DEVMATCH;    // (0x00000114) A device address match occurred on the last received
                                                        //              packet                                                     
        __IOM EVENTS_reg_t          EVENTS_DEVMISS;     // (0x00000118) No device address match occurred on the last
                                                        //              received packet                                            
        __IOM EVENTS_reg_t          EVENTS_RSSIEND;     // (0x0000011C) Sampling of receive signal strength complete               
        __IM  uint32_t              RESERVED1[2];       
        __IOM EVENTS_reg_t          EVENTS_BCMATCH;     // (0x00000128) Bit counter reached bit count value                        
        __IM  uint32_t              RESERVED2;
        __IOM EVENTS_reg_t          EVENTS_CRCOK;       // (0x00000130) Packet received with CRC ok                                
        __IOM EVENTS_reg_t          EVENTS_CRCERROR;    // (0x00000134) Packet received with CRC error                             
        __IOM EVENTS_reg_t          EVENTS_FRAMESTART;  // (0x00000138) IEEE 802.15.4 length field received                        
        __IOM EVENTS_reg_t          EVENTS_EDEND;       // (0x0000013C) Sampling of energy detection complete. A new
                                                        //              ED sample is ready for readout from the
                                                        //              RADIO.EDSAMPLE register                                   
        __IOM EVENTS_reg_t          EVENTS_EDSTOPPED;   // (0x00000140) The sampling of energy detection has stopped               
        __IOM EVENTS_reg_t          EVENTS_CCAIDLE;     // (0x00000144) Wireless medium in idle - clear to send                    
        __IOM EVENTS_reg_t          EVENTS_CCABUSY;     // (0x00000148) Wireless medium busy - do not send                         
        __IOM EVENTS_reg_t          EVENTS_CCASTOPPED;  // (0x0000014C) The CCA has stopped                                        
        __IOM EVENTS_reg_t          EVENTS_RATEBOOST;   // (0x00000150) Ble_LR CI field received, receive mode is changed
                                                        //              from Ble_LR125Kbit to Ble_LR500Kbit.                      
        __IOM EVENTS_reg_t          EVENTS_TXREADY;     // (0x00000154) RADIO has ramped up and is ready to be started
                                                        //              TX path                                                    
        __IOM EVENTS_reg_t          EVENTS_RXREADY;     // (0x00000158) RADIO has ramped up and is ready to be started
                                                        //              RX path                                                    
        __IOM EVENTS_reg_t          EVENTS_MHRMATCH;    // (0x0000015C) MAC header match found                                     
        __IM  uint32_t              RESERVED3[3];
        __IOM EVENTS_reg_t          EVENTS_PHYEND;      // (0x0000016C) Generated when last bit is sent on air                     
        __IOM EVENTS_reg_t          EVENTS_CTEPRESENT;  // (0x00000170) CTE is present (early warning right after receiving
                                                        //              CTEInfo byte)                                              
        __IM  uint32_t              RESERVED4[35];
        __IOM SHORTS_reg_t          SHORTS;             // (0x00000200) Shortcuts between local events and tasks                   
        __IM  uint32_t              RESERVED5[64];
        __IOM INTENSET_reg_t        INTENSET;           // (0x00000304) Enable interrupt                                           
        __IOM INTENCLR_reg_t        INTENCLR;           // (0x00000308) Disable interrupt                                          
        __IM  uint32_t              RESERVED6[61];
        __IM  CRCSTATUS_reg_t       CRCSTATUS;          // (0x00000400) CRC status                                                 
        __IM  uint32_t              RESERVED7;
        __IM  RXMATCH_reg_t         RXMATCH;            // (0x00000408) Received address                                           
        __IM  RXCRC_reg_t           RXCRC;              // (0x0000040C) CRC field of previously received packet                    
        __IM  DAI_reg_t             DAI;                // (0x00000410) Device address match index                                 
        __IM  PDUSTAT_reg_t         PDUSTAT;            // (0x00000414) Payload status                                             
        __IM  uint32_t              RESERVED8[13];
        __IM  CTESTATUS_reg_t       CTESTATUS;          // (0x0000044C) CTEInfo parsed from received packet                        
        __IM  uint32_t              RESERVED9[2];
        __IM  DFESTATUS_reg_t       DFESTATUS;          // (0x00000458) DFE status information                                     
        __IM  uint32_t              RESERVED10[42];
        __IOM PACKETPTR_reg_t       PACKETPTR;          // (0x00000504) Packet pointer                                             
        __IOM FREQUENCY_reg_t       FREQUENCY;          // (0x00000508) Frequency                                                  
        __IOM TXPOWER_reg_t         TXPOWER;            // (0x0000050C) Output power                                               
        __IOM MODE_reg_t            MODE;               // (0x00000510) Data rate and modulation                                   
        __IOM PCNF0_reg_t           PCNF0;              // (0x00000514) Packet configuration register 0                            
        __IOM PCNF1_reg_t           PCNF1;              // (0x00000518) Packet configuration register 1                            
        __IOM BASE0_reg_t           BASE0;              // (0x0000051C) Base address 0                                             
        __IOM BASE1_reg_t           BASE1;              // (0x00000520) Base address 1                                             
        __IOM PREFIX0_reg_t         PREFIX0;            // (0x00000524) Prefixes bytes for logical addresses 0-3                   
        __IOM PREFIX1_reg_t         PREFIX1;            // (0x00000528) Prefixes bytes for logical addresses 4-7                   
        __IOM TXADDRESS_reg_t       TXADDRESS;          // (0x0000052C) Transmit address select                                    
        __IOM RXADDRESSES_reg_t     RXADDRESSES;        // (0x00000530) Receive address select                                     
        __IOM CRCCNF_reg_t          CRCCNF;             // (0x00000534) CRC configuration                                          
        __IOM CRCPOLY_reg_t         CRCPOLY;            // (0x00000538) CRC polynomial                                             
        __IOM CRCINIT_reg_t         CRCINIT;            // (0x0000053C) CRC initial value                                          
        __IM  uint32_t              RESERVED11;
        __IOM TIFS_reg_t            TIFS;               // (0x00000544) Interframe spacing in us                                   
        __IM  RSSISAMPLE_reg_t      RSSISAMPLE;         // (0x00000548) RSSI sample                                                
        __IM  uint32_t              RESERVED12;
        __IM  STATE_reg_t           STATE;              // (0x00000550) Current radio state                                        
        __IOM DATAWHITEIV_reg_t     DATAWHITEIV;        // (0x00000554) Data whitening initial value                               
        __IM  uint32_t              RESERVED13[2];
        __IOM BCC_reg_t             BCC;                // (0x00000560) Bit counter compare                                        
        __IM  uint32_t              RESERVED14[39];
        __IOM DAB_reg_t             DAB[8];             // (0x00000600) Description collection: Device address base segment
                                                        //              n                                                          
        __IOM DAP_reg_t             DAP[8];             // (0x00000620) Description collection: Device address prefix
                                                        //              n                                                         
        __IOM DACNF_reg_t           DACNF;              // (0x00000640) Device address match configuration                         
        __IOM MHRMATCHCONF_reg_t    MHRMATCHCONF;       // (0x00000644) Search pattern configuration                               
        __IOM MHRMATCHMAS_reg_t     MHRMATCHMAS;        // (0x00000648) Pattern mask                                               
        __IM  uint32_t              RESERVED15;
        __IOM MODECNF0_reg_t        MODECNF0;           // (0x00000650) Radio mode configuration register 0                        
        __IM  uint32_t              RESERVED16[3];
        __IOM SFD_reg_t             SFD;                // (0x00000660) IEEE 802.15.4 start of frame delimiter                     
        __IOM EDCNT_reg_t           EDCNT;              // (0x00000664) IEEE 802.15.4 energy detect loop count                     
        __IOM EDSAMPLE_reg_t        EDSAMPLE;           // (0x00000668) IEEE 802.15.4 energy detect level                          
        __IOM CCACTRL_reg_t         CCACTRL;            // (0x0000066C) IEEE 802.15.4 clear channel assessment control             
        __IM  uint32_t              RESERVED17[164];
        __IOM DFEMODE_reg_t         DFEMODE;            // (0x00000900) Whether to use Angle-of-Arrival (AOA) or Angle-of-Departure
                                                        //              (AOD)                                                      
        __IOM CTEINLINECONF_reg_t   CTEINLINECONF;      // (0x00000904) Configuration for CTE inline mode                          
        __IM  uint32_t              RESERVED18[2];
        __IOM DFECTRL1_reg_t        DFECTRL1;           // (0x00000910) Various configuration for Direction finding                
        __IOM DFECTRL2_reg_t        DFECTRL2;           // (0x00000914) Start offset for Direction finding                         
        __IM  uint32_t              RESERVED19[4];
        __IOM SWITCHPATTERN_reg_t   SWITCHPATTERN;      // (0x00000928) GPIO patterns to be used for each antenna                  
        __IOM CLEARPATTERN_reg_t    CLEARPATTERN;       // (0x0000092C) Clear the GPIO pattern array for antenna control           
        __IOM RADIO_PSEL_reg_t      PSEL;               // (0x00000930) Unspecified                                                
        __IOM RADIO_DFEPACKET_reg_t DFEPACKET;          // (0x00000950) DFE packet EasyDMA channel                                 
        __IM  uint32_t              RESERVED20[424];
        __IOM POWER_reg_t           POWER;              // (0x00000FFC) Peripheral power control                                   
    };                                                  // Size = 4096 (0x1000)   

    constexpr uint32_t rNRF_RADIO_BASE     = 0x40001000;
    
    constexpr NRF_RADIO_Type * MAIN_RADIO_regs = ((NRF_RADIO_Type *) rNRF_RADIO_BASE); 
}