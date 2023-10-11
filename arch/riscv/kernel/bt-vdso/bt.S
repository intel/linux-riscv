// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2023 Intel Corporation
 *
 * Author: Haicheng Li <haicheng.li@intel.com>
 * 	   Xiao Wang <xiao.w.wang@intel.com>
 *
 */

#include <linux/linkage.h>
#include <asm/asm.h>
#include <asm/asm-offsets.h>
#include <asm/unistd.h>
#include <vdso/soft_isa.h>

	.pushsection .bt
ENTRY(__vdso_bt)
	.cfi_startproc

_save_context:
	addi sp, sp, -(PT_SIZE_ON_STACK)
	REG_S x1,  PT_RA(sp)
	REG_S x3,  PT_GP(sp)
	REG_S x4,  PT_TP(sp)
	REG_S x5,  PT_T0(sp)
	REG_S x6,  PT_T1(sp)
	REG_S x7,  PT_T2(sp)
	REG_S x8,  PT_S0(sp)
	REG_S x9,  PT_S1(sp)
	REG_S x10, PT_A0(sp)
	REG_S x11, PT_A1(sp)
	REG_S x12, PT_A2(sp)
	REG_S x13, PT_A3(sp)
	REG_S x14, PT_A4(sp)
	REG_S x15, PT_A5(sp)
	REG_S x16, PT_A6(sp)
	REG_S x17, PT_A7(sp)
	REG_S x18, PT_S2(sp)
	REG_S x19, PT_S3(sp)
	REG_S x20, PT_S4(sp)
	REG_S x21, PT_S5(sp)
	REG_S x22, PT_S6(sp)
	REG_S x23, PT_S7(sp)
	REG_S x24, PT_S8(sp)
	REG_S x25, PT_S9(sp)
	REG_S x26, PT_S10(sp)
	REG_S x27, PT_S11(sp)
	REG_S x28, PT_T3(sp)
	REG_S x29, PT_T4(sp)
	REG_S x30, PT_T5(sp)
	REG_S x31, PT_T6(sp)

	mv t0, x2
	addi t0, t0, PT_SIZE_ON_STACK
	REG_S t0, PT_SP(sp)

	addi sp, sp, -PT_FP_VRF_SIZE

	fsd f0, PT_F0(sp)
	fsd f1, PT_F1(sp)
	fsd f2, PT_F2(sp)
	fsd f3, PT_F3(sp)
	fsd f4, PT_F4(sp)
	fsd f5, PT_F5(sp)
	fsd f6, PT_F6(sp)
	fsd f7, PT_F7(sp)
	fsd f8, PT_F8(sp)
	fsd f9, PT_F9(sp)
	fsd f10, PT_F10(sp)
	fsd f11, PT_F11(sp)
	fsd f12, PT_F12(sp)
	fsd f13, PT_F13(sp)
	fsd f14, PT_F14(sp)
	fsd f15, PT_F15(sp)
	fsd f16, PT_F16(sp)
	fsd f17, PT_F17(sp)
	fsd f18, PT_F18(sp)
	fsd f19, PT_F19(sp)
	fsd f20, PT_F20(sp)
	fsd f21, PT_F21(sp)
	fsd f22, PT_F22(sp)
	fsd f23, PT_F23(sp)
	fsd f24, PT_F24(sp)
	fsd f25, PT_F25(sp)
	fsd f26, PT_F26(sp)
	fsd f27, PT_F27(sp)
	fsd f28, PT_F28(sp)
	fsd f29, PT_F29(sp)
	fsd f30, PT_F30(sp)
	fsd f31, PT_F31(sp)

	mv a0, sp
	call bt_entry

_restore_context:
	fld f0, PT_F0(sp)
	fld f1, PT_F1(sp)
	fld f2, PT_F2(sp)
	fld f3, PT_F3(sp)
	fld f4, PT_F4(sp)
	fld f5, PT_F5(sp)
	fld f6, PT_F6(sp)
	fld f7, PT_F7(sp)
	fld f8, PT_F8(sp)
	fld f9, PT_F9(sp)
	fld f10, PT_F10(sp)
	fld f11, PT_F11(sp)
	fld f12, PT_F12(sp)
	fld f13, PT_F13(sp)
	fld f14, PT_F14(sp)
	fld f15, PT_F15(sp)
	fld f16, PT_F16(sp)
	fld f17, PT_F17(sp)
	fld f18, PT_F18(sp)
	fld f19, PT_F19(sp)
	fld f20, PT_F20(sp)
	fld f21, PT_F21(sp)
	fld f22, PT_F22(sp)
	fld f23, PT_F23(sp)
	fld f24, PT_F24(sp)
	fld f25, PT_F25(sp)
	fld f26, PT_F26(sp)
	fld f27, PT_F27(sp)
	fld f28, PT_F28(sp)
	fld f29, PT_F29(sp)
	fld f30, PT_F30(sp)
	fld f31, PT_F31(sp)

	addi sp, sp, PT_FP_VRF_SIZE;

	REG_L x1,  PT_RA(sp)
	REG_L x3,  PT_GP(sp)
	REG_L x4,  PT_TP(sp)
	REG_L x5,  PT_T0(sp)
	REG_L x6,  PT_T1(sp)
	REG_L x7,  PT_T2(sp)
	REG_L x8,  PT_S0(sp)
	REG_L x9,  PT_S1(sp)
	REG_L x10, PT_A0(sp)
	REG_L x11, PT_A1(sp)
	REG_L x12, PT_A2(sp)
	REG_L x13, PT_A3(sp)
	REG_L x14, PT_A4(sp)
	REG_L x15, PT_A5(sp)
	REG_L x16, PT_A6(sp)
	REG_L x17, PT_A7(sp)
	REG_L x18, PT_S2(sp)
	REG_L x19, PT_S3(sp)
	REG_L x20, PT_S4(sp)
	REG_L x21, PT_S5(sp)
	REG_L x22, PT_S6(sp)
	REG_L x23, PT_S7(sp)
	REG_L x24, PT_S8(sp)
	REG_L x25, PT_S9(sp)
	REG_L x26, PT_S10(sp)
	REG_L x27, PT_S11(sp)
	REG_L x28, PT_T3(sp)
	REG_L x29, PT_T4(sp)
	REG_L x30, PT_T5(sp)
	REG_L x31, PT_T6(sp)

	j .L0
.L0:
	.word 0
	.word 0x87654321
	.cfi_endproc
ENDPROC(__vdso_bt)
