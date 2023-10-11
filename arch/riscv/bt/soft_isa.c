/* SPDX-License-Identifier: GPL-2.0-only
 *
 * Copyright (C) 2023 Intel Corporation 
 *
 * Author: Haicheng Li <haicheng.li@intel.com>
 * 	   Xiao Wang <xiao.w.wang@intel.com>
 *
 */

#include <linux/cpu.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/debug.h>
#include <linux/sched/signal.h>
#include <linux/signal.h>
#include <linux/kdebug.h>
#include <linux/uaccess.h>
#include <linux/kprobes.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/kexec.h>

#include <asm/page.h>
#include <asm/asm-prototypes.h>
#include <asm/bug.h>
#include <asm/csr.h>
#include <asm/processor.h>
#include <asm/ptrace.h>
#include <asm/thread_info.h>

#include <vdso/datapage.h>
#include <vdso/soft_isa.h>

int soft_isa_exec(struct pt_regs *regs)
{
	struct task_struct *t = current;
	u64 level = t->thread.bt_nest_lvl;
	u64 *u_sp;

	if (level >= BT_MAX_NEST_LEVEL)
		return -1;

	if (*(int *)(regs->epc) == 0x0 &&
			*(int *)(regs->epc + 4) == 0x87654321) {
		struct pt_regs *user_regs = (struct pt_regs *)(regs->sp);
		regs->epc = user_regs->bt_ra;
		t->thread.bt_cbs[level] = user_regs->bt_cb;
		regs->sp = user_regs->sp;
	} else {
		regs->bt_ra = regs->epc;
		regs->bt_cb = t->thread.bt_cbs[level];
		regs->epc = (u64)t->mm->context.bt_vdso + BT_VDSO_TEXT_OFFSET;

		u_sp = (u64 *)(regs->sp);
		*(u_sp - 1) = regs->bt_ra;
		*(u_sp - 2) = regs->bt_cb;
	}
	return 0;
}
