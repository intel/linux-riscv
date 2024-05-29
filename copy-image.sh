#!/bin/bash

set -x

cp vmlinux initrd ~/acrn-riscv/hypervisor/
cp vmlinux ~/acrn-riscv/hypervisor/vmlinux.sos
