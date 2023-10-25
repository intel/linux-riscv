/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 * Copyright (C) 2023 Intel Corporation
 */
#include <asm/page.h>
#include <asm/vdso.h>
#include <vdso/soft_isa.h>

OUTPUT_ARCH(riscv)

SECTIONS
{
	PROVIDE(bt_vdso_A = BT_VDSO_ADDR);
	. = bt_vdso_A + SIZEOF_HEADERS;

	.hash		: { *(.hash) }			:text
	.gnu.hash	: { *(.gnu.hash) }
	.dynsym		: { *(.dynsym) }
	.dynstr		: { *(.dynstr) }
	.gnu.version	: { *(.gnu.version) }
	.gnu.version_d	: { *(.gnu.version_d) }
	.gnu.version_r	: { *(.gnu.version_r) }

	.note		: { *(.note.*) }
	.dynamic	: { *(.dynamic) }

	.eh_frame_hdr	: { *(.eh_frame_hdr) }
	.eh_frame	: { KEEP (*(.eh_frame)) }

	/*
	 * This linker script is used both with -r and with -shared.
	 * For the layouts to match, we need to skip more than enough
	 * space for the dynamic symbol table, etc. If this amount is
	 * insufficient, ld -shared will error; simply increase it here.
	 */

	. = BT_VDSO_TEXT_STATIC_ADDR;
	PROVIDE_HIDDEN (__ucbt_entry = .);
	.text	: { KEEP(*(.bt)) *(.text .text.*) }

	. = ALIGN(8);
	 __ucbt_rel_start = .;
	.got	: { *(.got.plt) *(.igot.plt) *(.got) *(.igot) }
	.data	: {
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		*(.rodata1)
		*(.sdata2 .sdata2.* .gnu.linkonce.s2.*)

		*(.data .data.* .gnu.linkonce.d.*)
		SORT(CONSTRUCTORS)
		*(.data1)
		*(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata .srodata.*)
		*(.sdata .sdata.* .gnu.linkonce.s.*)
	__ucbt_rel_end = .;

		*(.dynsbss)
		*(.sbss .sbss.* .gnu.linkonce.sb.*)
		*(.scommon)
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
	}
}

/*
 * We must supply the ELF program headers explicitly to get just one
 * PT_LOAD segment, and set the flags explicitly to make segments read-only.
 */
PHDRS
{
	text		PT_LOAD		FLAGS(5) FILEHDR PHDRS; /* PF_R|PF_X */
	dynamic		PT_DYNAMIC	FLAGS(4);		/* PF_R */
	note		PT_NOTE		FLAGS(4);		/* PF_R */
	eh_frame_hdr	PT_GNU_EH_FRAME;
}

/*
 * This controls what symbols we export from the DSO.
 */
VERSION
{
	LINUX_4.15 {
	global:
		__vdso_bt;
	local: *;
	};
}
