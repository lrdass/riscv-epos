// EPOS RISC-V Program Starter
 .file "rv32_crt0.S"

.section .text
.global asm_trap_vector
.align 4
asm_trap_vector:
	# Save registers
	addi sp, sp, -128    # Make some space in the stack
	sw ra, 0(sp)         # Return address
	sw a0, 8(sp)         # Function argument / return value
	sw a1, 16(sp)        # Function argument / return value
	sw a2, 24(sp)        # Function argument
	sw a3, 32(sp)        # Function argument
	sw a4, 40(sp)        # Function argument
	sw a5, 48(sp)        # Function argument
	sw a6, 56(sp)        # Function argument
	sw a7, 64(sp)        # Function argument
	sw t0, 72(sp)        # Temporary / alternate return address
	sw t1, 80(sp)        # Temporary
	sw t2, 88(sp)        # Temporary
	sw t3, 96(sp)        # Temporary
	sw t4, 104(sp)       # Temporary
	sw t5, 112(sp)       # Temporary
	sw t6, 120(sp)       # Temporary

	# Set arguments and call m_trap
	csrr	a0, mepc     # Machine exception pc
	csrr	a1, mtval    # Machine bad address or instruction
	csrr	a2, mcause   # Machine trap cause
	csrr	a3, mhartid  # Machine hart id
	csrr	a4, mstatus  # Machine status
	csrr	a5, mscratch # Scratch resgister for machine trap handlers
	call	m_trap

	# Restore registers
	lw ra, 0(sp)         # Return address
	lw a0, 8(sp)         # Function argument / return value
	lw a1, 16(sp)        # Function argument / return value
	lw a2, 24(sp)        # Function argument
	lw a3, 32(sp)        # Function argument
	lw a4, 40(sp)        # Function argument
	lw a5, 48(sp)        # Function argument
	lw a6, 56(sp)        # Function argument
	lw a7, 64(sp)        # Function argument
	lw t0, 72(sp)        # Temporary / alternate return address
	lw t1, 80(sp)        # Temporary
	lw t2, 88(sp)        # Temporary
	lw t3, 96(sp)        # Temporary
	lw t4, 104(sp)       # Temporary
	lw t5, 112(sp)       # Temporary
	lw t6, 120(sp)       # Temporary

	addi sp, sp, 128
	// disable interrupts
	# m_trap will return the return address via a0.

	# csrw	mepc, a0
	# Now load the trap frame back into t6
	# csrr	t6, mscratch
	mret

       

        // Entry point called by SETUP for processors
        .section .text
        .align  4
        .global _start
        .type   _start, function
_start:
        // Temporary stack(s) for INIT are created and configure by SETUP

        // Only hart (core) 0 cleans cache
        // IMPLEMENT

        // Set all bytes in the BSS section to zero.
        la      a0, __bss_start
        la      a1, _end
        bgeu    a0, a1, 2f
1:
        sw      zero, (a0)
        addi    a0, a0, 4
        bltu    a0, a1, 1b
2:
        // Call _init
        call      _init

        // Call main
        .align  4
        .globl  __epos_app_entry
        .type   __epos_app_entry, function
__epos_app_entry:
        call      main
        lw        a0, 0(sp)         // save main's return value to be used by exit()
        call      _fini
        call      _exit
