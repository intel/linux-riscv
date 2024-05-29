#!/bin/bash

set -x

cp arch/riscv/boot/Image ~/acrn-riscv/hypervisor/Image.uos
cp initrd ~/acrn-riscv/hypervisor/
cp vmlinux ~/acrn-riscv/hypervisor/vmlinux.uos
