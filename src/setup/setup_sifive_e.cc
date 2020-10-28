// EPOS RISC-V sifive SETUP

#include <system/config.h>

extern "C" { void _vector_table() __attribute__ ((used, naked, section(".init"))); }

// Interrupt Vector Table
void _vector_table()
{   
        // aqui sabemos que será o mapeamento para a vector table no futuro
 ASM("\t\n\
        j _start                            \t\n\
        ");
};