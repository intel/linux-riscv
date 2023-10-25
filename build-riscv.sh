#!/bin/bash

set -x

make -j10 ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- UC_BUILD=~/bt-unicorn/build/ MUSL_BUILD=~/bt-musl/build/install/lib
#make -j10 ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu-
#make -j4 ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu-
mkdir -p install
INSTALL_MOD_PATH=`pwd`/install make  ARCH=riscv modules_install
./create-initrd.sh initramfs-template install initrd
