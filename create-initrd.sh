#!/bin/bash

function usage()
{
	prog=$(basename "$0")
	echo "create initramfs from existing template and new kernel modules"
	echo "	./$prog old_initrd new_module_path new_initrd"
	exit 1
}

if [[ $# < 3 ]]; then
	usage
fi

old_initrd=$1
new_module_path=$2
new_initrd=$3

workdir=$(mktemp -d initrd.XXX)
zcat "$1" | cpio -id -D "$workdir"
rm -rf "$workdir/lib/modules"
(cd "$new_module_path"; tar cf - lib/modules/*/kernel/drivers/block) | tar xf - -C "$workdir"
(cd "$new_module_path"; tar cf - lib/modules/*/kernel/drivers/virtio) | tar xf - -C "$workdir"
(cd "$new_module_path"; tar cf - --no-recursion lib/modules/*/modules*) | tar xf - -C "$workdir"
(cd "$workdir"; find . | cpio -o --format=newc) | gzip -9 > "$new_initrd"
rm -rf "$workdir"
