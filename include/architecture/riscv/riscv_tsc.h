// EPOS ARMv7 Time-Stamp Counter Mediator Declarations

#ifndef __riscv_tsc_h
#define __riscv_tsc_h

#include <architecture/cpu.h>
#include <architecture/tsc.h>

__BEGIN_SYS

class TSC: private TSC_Common
{

    friend class CPU;
    friend class IC;
    
public:
    using TSC_Common::Time_Stamp;
public:
    TSC() {}

    static Hertz frequency() { return CPU::clock(); }
    static PPB accuracy() { return 50; }

    static Time_Stamp time_stamp() {
        Time_Stamp ts;
        ASM("rdtsc" : "=A" (ts) : ); // must be volatile!
        return ts;
    }

    static void time_stamp(const Time_Stamp & ts) ;
    
};

__END_SYS

#endif
