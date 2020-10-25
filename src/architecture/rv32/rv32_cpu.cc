// EPOS RISC-V 32 CPU Mediator Implementation

#include <architecture/rv32/rv32_cpu.h>
#include <system.h>

__BEGIN_SYS

// Class attributes
unsigned int CPU::_cpu_clock;
unsigned int CPU::_bus_clock;

// Class methods
void CPU::Context::save() volatile
{
    // implement
    ASM("addi sp, sp, -128           \t\n\
        sw ra, 0(sp)                \t\n\
        sw a0, 8(sp)                \t\n\
        sw a1, 16(sp)               \t\n\
        sw a2, 24(sp)               \t\n\
        sw a3, 32(sp)               \t\n\
        sw a4, 40(sp)               \t\n\
        sw a5, 48(sp)               \t\n\
        sw a6, 56(sp)               \t\n\
        sw a7, 64(sp)               \t\n\
        sw t0, 72(sp)               \t\n\
        sw t1, 80(sp)               \t\n\
        sw t2, 88(sp)               \t\n\
        sw t3, 96(sp)               \t\n\
        sw t4, 104(sp)              \t\n\
        sw t5, 112(sp)              \t\n\
        sw t6, 120(sp)              \t\n\
    ");
}

void CPU::Context::load() const volatile
{
    ASM("lw ra, 0(sp)         \t\n\
        lw a0, 8(sp)         \t\n\
        lw a1, 16(sp)        \t\n\
        lw a2, 24(sp)        \t\n\
        lw a3, 32(sp)        \t\n\
        lw a4, 40(sp)        \t\n\
        lw a5, 48(sp)        \t\n\
        lw a6, 56(sp)        \t\n\
        lw a7, 64(sp)        \t\n\
        lw t0, 72(sp)        \t\n\
        lw t1, 80(sp)        \t\n\
        lw t2, 88(sp)        \t\n\
        lw t3, 96(sp)        \t\n\
        lw t4, 104(sp)       \t\n\
        lw t5, 112(sp)       \t\n\
        lw t6, 120(sp)       \t\n\
        addi sp, sp, 128     \t\n\
    ");
    // implement
}

void CPU::switch_context(Context ** o, Context * n)
{
    ASM("nop");
    // implement
}

__END_SYS
