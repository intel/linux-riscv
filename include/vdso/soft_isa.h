/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __VDSO_SOFT_ISA_H
#define __VDSO_SOFT_ISA_H

#ifndef __ASSEMBLY__
#include <linux/percpu.h>
#include <uapi/linux/types.h>
#include <vdso/datapage.h>

__attribute__((packed))
struct pt_regs_fp {
	double f0;
	double f1;
	double f2;
	double f3;
	double f4;
	double f5;
	double f6;
	double f7;
	double f8;
	double f9;
	double f10;
	double f11;
	double f12;
	double f13;
	double f14;
	double f15;
	double f16;
	double f17;
	double f18;
	double f19;
	double f20;
	double f21;
	double f22;
	double f23;
	double f24;
	double f25;
	double f26;
	double f27;
	double f28;
	double f29;
	double f30;
	double f31;
};

__attribute__((packed))
struct pt_regs_ext {
	struct pt_regs_fp fps;
	struct pt_regs ints;
};

#endif /* !__ASSEMBLY__ */

#define PT_F0 0
#define PT_F1 8
#define PT_F2 16
#define PT_F3 24
#define PT_F4 32
#define PT_F5 40
#define PT_F6 48
#define PT_F7 56
#define PT_F8 64
#define PT_F9 72
#define PT_F10 80
#define PT_F11 88
#define PT_F12 96
#define PT_F13 104
#define PT_F14 112
#define PT_F15 120
#define PT_F16 128
#define PT_F17 136
#define PT_F18 144
#define PT_F19 152
#define PT_F20 160
#define PT_F21 168
#define PT_F22 176
#define PT_F23 184
#define PT_F24 192
#define PT_F25 200
#define PT_F26 208
#define PT_F27 216
#define PT_F28 224
#define PT_F29 232
#define PT_F30 240
#define PT_F31 248
/* 32 FP regs take 256 bytes (assume D extension) */
#define PT_FP_VRF_SIZE 256

/* Find a free addr range to host bt-vdso sections */
/* #define BT_VDSO_ADDR 0xff1c000000000000 */
#define BT_VDSO_ADDR		0x6000000
#define BT_VDSO_TEXT_OFFSET	0x60000
#define BT_VDSO_DATA_OFFSET	0x6000000
#define BT_VDSO_END		0x10000000

#endif /* __VDSO_SOFT_ISA_H */
