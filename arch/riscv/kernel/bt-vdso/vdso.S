/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2023 Intel Corporation
 *
 * Author: Haicheng Li <haicheng.li@intel.com>
 *
 */

#include <linux/init.h>
#include <linux/linkage.h>
#include <asm/page.h>

#ifndef __BT_VDSO_PATH
#define __BT_VDSO_PATH "arch/riscv/kernel/bt-vdso/vdso.so"
#endif

	__PAGE_ALIGNED_DATA

	.globl bt_vdso_start, bt_vdso_end
	.balign PAGE_SIZE
bt_vdso_start:
	.incbin __BT_VDSO_PATH
	.balign PAGE_SIZE
bt_vdso_end:

	.previous
