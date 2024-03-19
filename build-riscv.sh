#!/bin/bash

set -x

cp arch/riscv/configs/hvp_defconfig .config

make -j10 ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-
#make -j10 ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-
#make -j4 ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu-
mkdir -p install
INSTALL_MOD_PATH=`pwd`/install make  ARCH=riscv modules_install
#./create-initrd.sh initramfs-template install initrd
