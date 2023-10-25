#!/bin/bash

set -x

cp arch/riscv/boot/Image ~/bt-img/Image.bt
cp initrd ~/bt-img/initrd.bt
cp vmlinux ~/bt-img/vmlinux.bt
cp arch/riscv/kernel/bt-vdso/vdso.so.dbg ~/bt-img/vdso.so.dbg.bt
cp soft_isa.gdb ~/bt-img/
