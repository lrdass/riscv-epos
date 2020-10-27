// EPOS RISC-V UART Mediator Declarations

#ifndef __riscv_uart_h
#define __riscv_uart_h

#include <architecture/cpu.h>
#include <machine/uart.h>
#include <system/memory_map.h>

__BEGIN_SYS

class UART: private UART_Common
{
private:

    typedef CPU::Reg8 Reg8;
    typedef CPU::Reg32 Reg32;

    static const unsigned int UNIT = Traits<UART>::DEF_UNIT;
    static const unsigned int BAUD_RATE = Traits<UART>::DEF_BAUD_RATE;
    static const unsigned int DATA_BITS = Traits<UART>::DEF_DATA_BITS;
    static const unsigned int PARITY = Traits<UART>::DEF_PARITY;
    static const unsigned int STOP_BITS = Traits<UART>::DEF_STOP_BITS;
    
    // conferir
    static const unsigned int CLOCK = Traits<UART>::CLOCK;

    // typedef UART_Engine Engine;

    enum {
        
        THR      = 0x000, // Transmit Holding	W,   DLAB = 0
        RBR      = 0x000, // Receive Buffer 	R,   DLAB = 0
        IER      = 0x001, // Interrupt Enable	R/W, DLAB = 0 [0=DR,1=THRE,2=LI,3=MO]
        FCR      = 0x002, // FIFO Control	W   [0=EN,1=RC,2=XC,3=RDY,67=TRG]
        IIR      = 0x002, // Interrupt Id	R   [0=PEN,12=ID,3=FIFOTO,67=1]
        LCR      = 0x003, // Line Control	R/W [01=DL,2=SB,345=P,6=BRK,7=DLAB]
        MCR      = 0x004, // Modem Control	R/W [0=DTR,1=RTS,2=OUT1,3=OUT2,4=LB]
        LSR      = 0x005, // Line Status		R/W [0=DR,1=OE,2=PE,3=FE,4=BI,5=THRE,
                 //			     6=TEMT,7=FIFOE]
        MSR      = 0x006, // Modem Status	R/W [0=CTS,1=DSR,2=RI,3=DCD,4=LBCTS,
                 // 			     5=LBDSR,6=LBRI,7=LBDCD]
        SCR      = 0x007, // Scratch 		R/W
        DLL      = 0x000, /* Divisor LSB (LCR_DLAB) */
        DLM      = 0x001  /* Divisor MSB (LCR_DLAB) */
        
    };

    // uart useful bits
    enum {
        LSR_DA   = 0x01,
        LSR_RI   = 0x40,
        LCR_PODD = 0x08,
        LCR_8BIT = 0x03
    };



public:
    using UART_Common::NONE;
    using UART_Common::EVEN;
    using UART_Common::ODD;

public:
    UART(unsigned int unit = UNIT, unsigned int baud_rate = BAUD_RATE, unsigned int data_bits = DATA_BITS, unsigned int parity = PARITY, unsigned int stop_bits = STOP_BITS) 
    {
        config(baud_rate, data_bits, parity, stop_bits);
    }
void config(unsigned int brate, unsigned int dbits, unsigned int par, unsigned int sbits)
    {
        // Disable all interrupts
        uart(IER) = 0;

        // Set clock divisor
        Reg32 div = CLOCK / brate;
        dlab(true);
        uart(DLL) = div;
        uart(DLM) = div >> 8;
        dlab(false);

        // Set data word length (5, 6, 7 or 8)
        Reg8 lcr = dbits - 5;

        // Set parity (0 [no], 1 [odd], 2 [even])
        if (par)
        {
            lcr |= 1 << 3;
            lcr |= (par - 1) << 4;
        }

        // Set stop-bits (1, 2 or 3 [1.5])
        lcr |= (sbits > 1) ? (1 << 2) : 0;

        uart(LCR) = lcr;
        
        // Enables Tx and Rx FIFOs, clear them, set trigger to 14 bytes
        uart(FCR) = 0xc7;

        // Set DTR, RTS and OUT2 of MCR
        uart(MCR) = uart(MCR) | 0x0b;
    }

    void config(unsigned int *brate, unsigned int *dbits, unsigned int *par, unsigned int *sbits)
    {
        // Get clock divisor
        dlab(true);
        *brate = CLOCK * ((uart(DLM) << 8) | uart(DLL));
        dlab(false);

        Reg32 lcr = uart(LCR);

        // Get data word length (LCR bits 0 and 1)
        *dbits = (lcr & 0x03) + 5;

        // Get parity (LCR bits 3 [enable] and 4 [odd/even])
        *par = (lcr & 0x08) ? ((lcr & 0x10) ? 2 : 1) : 0;

        // Get stop-bits  (LCR bit 2 [0 - >1, 1&D5 -> 1.5, 1&!D5 -> 2)
        *sbits = (lcr & 0x04) ? ((*dbits == 5) ? 3 : 2) : 1;
    }

    Reg8 rxd() { return uart(RBR); }
    void txd(Reg8 c) { uart(THR) = c; }

    void int_enable(bool receive = true, bool send = true, bool line = true, bool modem = true)
    {
        uart(IER) = receive | (send << 1) | (line << 2) | (modem << 3);
    }
    void int_disable(bool receive = true, bool send = true, bool line = true, bool modem = true)
    {
        uart(IER) = uart(IER) & ~(receive | (send << 1) | (line << 2) | (modem << 3));
    }

    void reset()
    {
        // Reconfiguring the UART implicitly resets it
        unsigned int b, db, p, sb;
        config(&b, &db, &p, &sb);
        config(b, db, p, sb);
    }

    void loopback(bool flag) { uart(MCR) = uart(MCR) | (flag << 4); }

    bool rxd_ok() { return uart(LSR) & LSR_DA; }
    bool txd_ok() { return !((uart(LSR) & LSR_RI) == 0); }

    void dtr() { uart(MCR) = uart(MCR) | (1 << 0); }
    void rts() { uart(MCR) = uart(MCR) | (1 << 1); }
    bool cts() { return uart(MSR) & (1 << 0); }
    bool dsr() { return uart(MSR) & (1 << 1); }
    bool dcd() { return uart(MSR) & (1 << 3); }
    bool ri() { return uart(MSR) & (1 << 2); }

    bool overrun_error() { return uart(LSR) & (1 << 1); }
    bool parity_error() { return uart(LSR) & (1 << 2); }
    bool framing_error() { return uart(LSR) & (1 << 3); }

    void enable() {}
    void disable() {}


    char get() { while(!rxd_ok()); return rxd(); }
    void put(char c) { while(!txd_ok()); txd(c); }

    void flush() { while(!txd_empty()); }
    bool ready_to_get() { return rxd_ok(); }
    bool ready_to_put() { return txd_ok(); }

    bool txd_empty(){return false;}

    void power(const Power_Mode & mode) {}
private:

    void dlab(bool f) { uart(LCR) = (uart(LCR) & 0x7f) | (f << 7); }

private:
    volatile Reg8 & uart(unsigned int o) { return reinterpret_cast<volatile Reg8 *>(reinterpret_cast<void *>(this))[o]; }
};
__END_SYS

#endif
