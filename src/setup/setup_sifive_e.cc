// EPOS RISC-V sifive SETUP

#include <system/config.h>

extern "C" { void _vector_table() __attribute__ ((used, naked, section(".init"))); }

// Interrupt Vector Table
void _vector_table()
{   
  
 ASM("\t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1                 \t\n\
        .word   _int_entry + 1                 \t\n\
        .word   _int_entry + 1                 \t\n\
        .word   _int_entry + 1                 \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        .word   _int_entry + 1              \t\n\
        j _start                            \t\n\
        ");
};