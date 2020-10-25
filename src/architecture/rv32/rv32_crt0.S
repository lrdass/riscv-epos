        .file "rv32_crt0.S"
        
        .option norvc
        .altmacro
        .set NUM_GP_REGS, 32  # Number of registers per context
        .set REG_SIZE, 8   # Register size (in bytes)

        # Use macros for saving and restoring multiple registers
        .macro save_gp i, basereg=t6
                sw	x\i, ((\i)*REG_SIZE)(\basereg)
        .endm
        .macro load_gp i, basereg=t6
                lw	x\i, ((\i)*REG_SIZE)(\basereg)
        .endm
        .macro save_fp i, basereg=t6
                fsw	f\i, ((NUM_GP_REGS+(\i))*REG_SIZE)(\basereg)
        .endm
        .macro load_fp i, basereg=t6
                flw	f\i, ((NUM_GP_REGS+(\i))*REG_SIZE)(\basereg)
        .endm

        .option norvc
        .section .text
        .align  4
        .global c_save
        .type   c_save, function
c_save:
	csrrw	t6, mscratch, t6
	.set 	i, 0
	.rept	31
		save_gp	%i
		.set	i, i+1
	.endr
        mv		t5, t6
	csrr	t6, mscratch
	save_gp 31, t5
        # Restore the kernel trap frame into mscratch
	csrw	mscratch, t5

	csrr	t1, mstatus
	srli	t0, t1, 13
	andi	t0, t0, 3
	li		t3, 3
	bne		t0, t3, 1f
	# Save floating point registers
	.set 	i, 0
	.rept	32
		save_fp	%i, t5
		.set	i, i+1
	.endr
1:
        nop

        .option norvc
        .section .text
        .align  4
        .global c_load
        .type   c_load, function
c_load:
        csrr	t6, mscratch
	csrr	t1, mstatus
	srli	t0, t1, 13
	andi	t0, t0, 3
	li		t3, 3
	bne		t0, t3, 1f
	.set	i, 0
	.rept	32
		load_fp %i
		.set i, i+1
	.endr
1:
	# Restore all GP registers
	.set	i, 1
	.rept	31
		load_gp %i
		.set	i, i+1
	.endr
        
        .option norvc
        .section .text
        .align  4
        .global c_switch
        .type   c_switch, function
c_switch:

    csrw    mscratch, a0

	# Load program counter
	lw		a1, 520(a0)
	# Load satp
	lw		a2, 512(a0)
	# Load processor mode
	lw		a3, 552(a0)

	li		t0, 1 << 7 | 1 << 5 | 1 << 13
	slli	a3, a3, 11
	or		t0, t0, a3
	csrw	mstatus, t0
	csrw	mepc, a1
	csrw	satp, a2
	li		t1, 0xaaa
	csrw	mie, t1
	csrw	mtvec, t2
	mv	t6, a0
	.set	i, 0
	.rept	32
		load_fp %i
		.set i, i+1
	.endr
1:
	.set	i, 1
	.rept	31
		load_gp %i, t6
		.set	i, i+1
	.endr


        .option norvc
        .section .text
        .align  4
        .global _start
        .type   _start, function
_start:

                csrr t0, mhartid # reading CSR mhartid
	bnez t0, 4f

        la   sp, __boot_stack__
        .option push
        .option norelax
	la  gp, __global_pointer$
        .option pop

        la a0, __bss_start
        la a1, __BSS_END__
	bgeu a0, a1, 2f
1:
        sw	zero, (a0)
	addi	a0, a0, 4
	bltu	a0, a1, 1b

2:

        
        # Set all bytes in the BSS section to zero.
        la sp, __boot_stack__
        la t2, _vector_table
        # csrw	mstatus, t0
        # la t1, _init

        # csrw	mepc, t1
        csrw    mtvec, t2
        # la		ra, 4f
        # implement

        # Call _init
        # call _init

        call _init

        # Call main
        .align  4
        .globl  __epos_app_entry
        .type   __epos_app_entry, function
4:
        wfi
	j 4b
__epos_app_entry:
        call      main
        lw        a0, 0(sp)         #save main's return value to be used by exit()
        call      _fini
        call      _exit
