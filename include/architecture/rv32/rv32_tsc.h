// EPOS RISC-V 32 Time-Stamp Counter Mediator Declarations

#ifndef __riscv32_tsc_h
#define __riscv32_tsc_h

#include <architecture/cpu.h>
#include <architecture/tsc.h>
#include <system/memory_map.h>

__BEGIN_SYS

class TSC: private TSC_Common
{
    friend class CPU;
    friend class IC;

private:
    static const unsigned int CLOCK = Traits<Machine>::TIMER_CLOCK;
    static const unsigned int ACCURACY = 40000; // this is actually unknown at the moment

    // Registers offsets from CLINT_BASE
    enum {
        /**
        Address         Description     Note
        BASE + 0x0      msip            Machine mode software interrupt (IPI)
        BASE + 0x4000   mtimecmp        Machine mode timer compare register for Hart 0
        BASE + 0xBFF8   mtime           Timer register
        **/
        MTIMECMP        = 0X00004000,
        MTIME           = 0x0000BFF8
    };

public:
    using TSC_Common::Time_Stamp;

    static const unsigned int FREQUENCY = CLOCK;

public:
    TSC() {}

    static Hertz frequency() { return CLOCK; }
    static PPB accuracy() { return ACCURACY; }

    static Time_Stamp time_stamp() { 
        // IMPLEMENT
        return CPU::Reg64(0);
    }

private:
    static void init() {}

    static volatile CPU::Reg32 & reg(unsigned int o) { return reinterpret_cast<volatile CPU::Reg32 *>(Memory_Map::CLINT_BASE)[o / sizeof(CPU::Reg32)]; }
};

__END_SYS

#endif
