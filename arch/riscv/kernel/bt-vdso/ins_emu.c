/* Unicorn Emulator Engine */

#include <uapi/asm/ptrace.h>
#include <vdso/soft_isa.h>
#include "unicorn.h"

// memory address where emulation starts
#define ADDRESS 0x1000

static void bt_context_save(uc_engine *uc, struct pt_regs_ext *regs)
{
	uc_reg_write(uc, UC_RISCV_REG_X1, &regs->ints.ra);
	uc_reg_write(uc, UC_RISCV_REG_X2, &regs->ints.sp);
	uc_reg_write(uc, UC_RISCV_REG_X3, &regs->ints.gp);
	uc_reg_write(uc, UC_RISCV_REG_X4, &regs->ints.tp);
	uc_reg_write(uc, UC_RISCV_REG_X5, &regs->ints.t0);
	uc_reg_write(uc, UC_RISCV_REG_X6, &regs->ints.t1);
	uc_reg_write(uc, UC_RISCV_REG_X7, &regs->ints.t2);
	uc_reg_write(uc, UC_RISCV_REG_X8, &regs->ints.s0);
	uc_reg_write(uc, UC_RISCV_REG_X9, &regs->ints.s1);
	uc_reg_write(uc, UC_RISCV_REG_X10, &regs->ints.a0);
	uc_reg_write(uc, UC_RISCV_REG_X11, &regs->ints.a1);
	uc_reg_write(uc, UC_RISCV_REG_X12, &regs->ints.a2);
	uc_reg_write(uc, UC_RISCV_REG_X13, &regs->ints.a3);
	uc_reg_write(uc, UC_RISCV_REG_X14, &regs->ints.a4);
	uc_reg_write(uc, UC_RISCV_REG_X15, &regs->ints.a5);
	uc_reg_write(uc, UC_RISCV_REG_X16, &regs->ints.a6);
	uc_reg_write(uc, UC_RISCV_REG_X17, &regs->ints.a7);
	uc_reg_write(uc, UC_RISCV_REG_X18, &regs->ints.s2);
	uc_reg_write(uc, UC_RISCV_REG_X19, &regs->ints.s3);
	uc_reg_write(uc, UC_RISCV_REG_X20, &regs->ints.s4);
	uc_reg_write(uc, UC_RISCV_REG_X21, &regs->ints.s5);
	uc_reg_write(uc, UC_RISCV_REG_X22, &regs->ints.s6);
	uc_reg_write(uc, UC_RISCV_REG_X23, &regs->ints.s7);
	uc_reg_write(uc, UC_RISCV_REG_X24, &regs->ints.s8);
	uc_reg_write(uc, UC_RISCV_REG_X25, &regs->ints.s9);
	uc_reg_write(uc, UC_RISCV_REG_X26, &regs->ints.s10);
	uc_reg_write(uc, UC_RISCV_REG_X27, &regs->ints.s11);
	uc_reg_write(uc, UC_RISCV_REG_X28, &regs->ints.t3);
	uc_reg_write(uc, UC_RISCV_REG_X29, &regs->ints.t4);
	uc_reg_write(uc, UC_RISCV_REG_X30, &regs->ints.t5);
	uc_reg_write(uc, UC_RISCV_REG_X31, &regs->ints.t6);

	uc_reg_write(uc, UC_RISCV_REG_F0, &regs->fps.f0);
	uc_reg_write(uc, UC_RISCV_REG_F1, &regs->fps.f1);
	uc_reg_write(uc, UC_RISCV_REG_F2, &regs->fps.f2);
	uc_reg_write(uc, UC_RISCV_REG_F3, &regs->fps.f3);
	uc_reg_write(uc, UC_RISCV_REG_F4, &regs->fps.f4);
	uc_reg_write(uc, UC_RISCV_REG_F5, &regs->fps.f5);
	uc_reg_write(uc, UC_RISCV_REG_F6, &regs->fps.f6);
	uc_reg_write(uc, UC_RISCV_REG_F7, &regs->fps.f7);
	uc_reg_write(uc, UC_RISCV_REG_F8, &regs->fps.f8);
	uc_reg_write(uc, UC_RISCV_REG_F9, &regs->fps.f9);
	uc_reg_write(uc, UC_RISCV_REG_F10, &regs->fps.f10);
	uc_reg_write(uc, UC_RISCV_REG_F11, &regs->fps.f11);
	uc_reg_write(uc, UC_RISCV_REG_F12, &regs->fps.f12);
	uc_reg_write(uc, UC_RISCV_REG_F13, &regs->fps.f13);
	uc_reg_write(uc, UC_RISCV_REG_F14, &regs->fps.f14);
	uc_reg_write(uc, UC_RISCV_REG_F15, &regs->fps.f15);
	uc_reg_write(uc, UC_RISCV_REG_F16, &regs->fps.f16);
	uc_reg_write(uc, UC_RISCV_REG_F17, &regs->fps.f17);
	uc_reg_write(uc, UC_RISCV_REG_F18, &regs->fps.f18);
	uc_reg_write(uc, UC_RISCV_REG_F19, &regs->fps.f19);
	uc_reg_write(uc, UC_RISCV_REG_F20, &regs->fps.f20);
	uc_reg_write(uc, UC_RISCV_REG_F21, &regs->fps.f21);
	uc_reg_write(uc, UC_RISCV_REG_F22, &regs->fps.f22);
	uc_reg_write(uc, UC_RISCV_REG_F23, &regs->fps.f23);
	uc_reg_write(uc, UC_RISCV_REG_F24, &regs->fps.f24);
	uc_reg_write(uc, UC_RISCV_REG_F25, &regs->fps.f25);
	uc_reg_write(uc, UC_RISCV_REG_F26, &regs->fps.f26);
	uc_reg_write(uc, UC_RISCV_REG_F27, &regs->fps.f27);
	uc_reg_write(uc, UC_RISCV_REG_F28, &regs->fps.f28);
	uc_reg_write(uc, UC_RISCV_REG_F29, &regs->fps.f29);
	uc_reg_write(uc, UC_RISCV_REG_F30, &regs->fps.f30);
	uc_reg_write(uc, UC_RISCV_REG_F31, &regs->fps.f31);
}

static void bt_context_restore(uc_engine *uc, struct pt_regs_ext *regs)
{
	uc_reg_read(uc, UC_RISCV_REG_X1, &regs->ints.ra);
	uc_reg_read(uc, UC_RISCV_REG_X2, &regs->ints.sp);
	uc_reg_read(uc, UC_RISCV_REG_X3, &regs->ints.gp);
	uc_reg_read(uc, UC_RISCV_REG_X4, &regs->ints.tp);
	uc_reg_read(uc, UC_RISCV_REG_X5, &regs->ints.t0);
	uc_reg_read(uc, UC_RISCV_REG_X6, &regs->ints.t1);
	uc_reg_read(uc, UC_RISCV_REG_X7, &regs->ints.t2);
	uc_reg_read(uc, UC_RISCV_REG_X8, &regs->ints.s0);
	uc_reg_read(uc, UC_RISCV_REG_X9, &regs->ints.s1);
	uc_reg_read(uc, UC_RISCV_REG_X10, &regs->ints.a0);
	uc_reg_read(uc, UC_RISCV_REG_X11, &regs->ints.a1);
	uc_reg_read(uc, UC_RISCV_REG_X12, &regs->ints.a2);
	uc_reg_read(uc, UC_RISCV_REG_X13, &regs->ints.a3);
	uc_reg_read(uc, UC_RISCV_REG_X14, &regs->ints.a4);
	uc_reg_read(uc, UC_RISCV_REG_X15, &regs->ints.a5);
	uc_reg_read(uc, UC_RISCV_REG_X16, &regs->ints.a6);
	uc_reg_read(uc, UC_RISCV_REG_X17, &regs->ints.a7);
	uc_reg_read(uc, UC_RISCV_REG_X18, &regs->ints.s2);
	uc_reg_read(uc, UC_RISCV_REG_X19, &regs->ints.s3);
	uc_reg_read(uc, UC_RISCV_REG_X20, &regs->ints.s4);
	uc_reg_read(uc, UC_RISCV_REG_X21, &regs->ints.s5);
	uc_reg_read(uc, UC_RISCV_REG_X22, &regs->ints.s6);
	uc_reg_read(uc, UC_RISCV_REG_X23, &regs->ints.s7);
	uc_reg_read(uc, UC_RISCV_REG_X24, &regs->ints.s8);
	uc_reg_read(uc, UC_RISCV_REG_X25, &regs->ints.s9);
	uc_reg_read(uc, UC_RISCV_REG_X26, &regs->ints.s10);
	uc_reg_read(uc, UC_RISCV_REG_X27, &regs->ints.s11);
	uc_reg_read(uc, UC_RISCV_REG_X28, &regs->ints.t3);
	uc_reg_read(uc, UC_RISCV_REG_X29, &regs->ints.t4);
	uc_reg_read(uc, UC_RISCV_REG_X30, &regs->ints.t5);
	uc_reg_read(uc, UC_RISCV_REG_X31, &regs->ints.t6);
	uc_reg_read(uc, UC_RISCV_REG_PC, &regs->ints.bt_ra);

	uc_reg_read(uc, UC_RISCV_REG_F0, &regs->fps.f0);
	uc_reg_read(uc, UC_RISCV_REG_F1, &regs->fps.f1);
	uc_reg_read(uc, UC_RISCV_REG_F2, &regs->fps.f2);
	uc_reg_read(uc, UC_RISCV_REG_F3, &regs->fps.f3);
	uc_reg_read(uc, UC_RISCV_REG_F4, &regs->fps.f4);
	uc_reg_read(uc, UC_RISCV_REG_F5, &regs->fps.f5);
	uc_reg_read(uc, UC_RISCV_REG_F6, &regs->fps.f6);
	uc_reg_read(uc, UC_RISCV_REG_F7, &regs->fps.f7);
	uc_reg_read(uc, UC_RISCV_REG_F8, &regs->fps.f8);
	uc_reg_read(uc, UC_RISCV_REG_F9, &regs->fps.f9);
	uc_reg_read(uc, UC_RISCV_REG_F10, &regs->fps.f10);
	uc_reg_read(uc, UC_RISCV_REG_F11, &regs->fps.f11);
	uc_reg_read(uc, UC_RISCV_REG_F12, &regs->fps.f12);
	uc_reg_read(uc, UC_RISCV_REG_F13, &regs->fps.f13);
	uc_reg_read(uc, UC_RISCV_REG_F14, &regs->fps.f14);
	uc_reg_read(uc, UC_RISCV_REG_F15, &regs->fps.f15);
	uc_reg_read(uc, UC_RISCV_REG_F16, &regs->fps.f16);
	uc_reg_read(uc, UC_RISCV_REG_F17, &regs->fps.f17);
	uc_reg_read(uc, UC_RISCV_REG_F18, &regs->fps.f18);
	uc_reg_read(uc, UC_RISCV_REG_F19, &regs->fps.f19);
	uc_reg_read(uc, UC_RISCV_REG_F20, &regs->fps.f20);
	uc_reg_read(uc, UC_RISCV_REG_F21, &regs->fps.f21);
	uc_reg_read(uc, UC_RISCV_REG_F22, &regs->fps.f22);
	uc_reg_read(uc, UC_RISCV_REG_F23, &regs->fps.f23);
	uc_reg_read(uc, UC_RISCV_REG_F24, &regs->fps.f24);
	uc_reg_read(uc, UC_RISCV_REG_F25, &regs->fps.f25);
	uc_reg_read(uc, UC_RISCV_REG_F26, &regs->fps.f26);
	uc_reg_read(uc, UC_RISCV_REG_F27, &regs->fps.f27);
	uc_reg_read(uc, UC_RISCV_REG_F28, &regs->fps.f28);
	uc_reg_read(uc, UC_RISCV_REG_F29, &regs->fps.f29);
	uc_reg_read(uc, UC_RISCV_REG_F30, &regs->fps.f30);
	uc_reg_read(uc, UC_RISCV_REG_F31, &regs->fps.f31);
}

int bt_entry(struct pt_regs_ext *regs)
{
	uc_engine *uc;
	uc_err err;

	if (regs->ints.bt_cb != 0UL) {
		uc = (uc_engine *)regs->ints.bt_cb;
	} else {
		// Initialize emulator in RISCV64 mode
		err = uc_open(UC_ARCH_RISCV, UC_MODE_RISCV64, &uc);
		if (err)
			return err;
		else
			regs->ints.bt_cb = (unsigned long)uc;

		/* map 2^56 byte memory for this emulation, unicorn doesn't
		 * allow pointer of 0, so skip one page
		 */
		uc_mem_map_ptr(uc, ADDRESS, 0x100000000000000 - ADDRESS,
				UC_PROT_ALL, (void *)ADDRESS);
	}

	// initialize machine registers
	bt_context_save(uc, regs);

	// emulate machine code in infinite time (last param = 0), or when
	// finishing all the code.
	err = uc_emu_start(uc, regs->ints.bt_ra, regs->ints.bt_ra + 0x10 - 1, 0, 1);
	if (err) {
		//TBD, warning somewhere
		return err;
	}

	bt_context_restore(uc, regs);

	return 0;
}
