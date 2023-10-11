# SPDX-License-Identifier: GPL-2.0-only
# Copied from arch/tile/kernel/vdso/Makefile

ifeq ($(UC_BUILD),)
	$(error pls set UNICORN build path via env var UC_BUILD)
endif

# Absolute relocation type $(ARCH_REL_TYPE_ABS) needs to be defined before
# the inclusion of generic Makefile.
ARCH_REL_TYPE_ABS := R_RISCV_32|R_RISCV_64|R_RISCV_JUMP_SLOT
include $(srctree)/lib/vdso/Makefile
# Symbols present in the vdso
vdso-syms += bt
vdso-syms += ins_emu
#  CFLAGS_bt.o += -fPIC -static-pie -fPIE
#  CFLAGS_ins_emu.o += -fPIC -static-pie -fPIE

# Files to link into the vdso
obj-vdso = $(patsubst %, %.o, $(vdso-syms)) note.o

ccflags-y := -fno-stack-protector
ccflags-y += -DDISABLE_BRANCH_PROFILING

# Build rules
targets := $(obj-vdso) vdso.so vdso.so.dbg vdso.lds
obj-vdso := $(addprefix $(obj)/, $(obj-vdso))

obj-y += vdso.o
CPPFLAGS_vdso.lds += -P -C -U$(ARCH)

# Disable profiling and instrumentation for VDSO code
GCOV_PROFILE := n
KCOV_INSTRUMENT := n
KASAN_SANITIZE := n
UBSAN_SANITIZE := n

# Force dependency
$(obj)/vdso.o: $(obj)/vdso.so

# link rule for the .so file, .lds has to be first
$(obj)/vdso.so.dbg: $(obj)/vdso.lds $(obj-vdso) FORCE
	$(call if_changed,vdsold)
#LDFLAGS_vdso.so.dbg = -shared -Bsymbolic -warn-unresolved-symbols -soname=linux-vdso.so.1 -L $(src) -lunicorn \
#                   -L /usr/riscv64-linux-gnu/lib/ -lc -lm \
#                   -L /usr/lib/gcc-cross/riscv64-linux-gnu/9/ -latomic -lgcc \
#	--build-id=sha1 --hash-style=both --eh-frame-hdr
LDFLAGS_vdso.so.dbg = -static -warn-unresolved-symbols -soname=linux-bt-vdso.so.1 -L $(UC_BUILD) -lunicorn \
                   -L /usr/riscv64-linux-gnu/lib/ -lc -lm \
                   -L /usr/lib/gcc-cross/riscv64-linux-gnu/9/ -latomic -lgcc \
	--build-id=sha1 --hash-style=both --eh-frame-hdr

# strip rule for the .so file
$(obj)/%.so: OBJCOPYFLAGS := -S
$(obj)/%.so: $(obj)/%.so.dbg FORCE
	$(call if_changed,objcopy)

# Generate bt-VDSO offsets using helper script
gen-vdsosym := $(srctree)/$(src)/gen_vdso_offsets.sh
quiet_cmd_vdsosym = VDSOSYM $@
	cmd_vdsosym = $(NM) $< | $(gen-vdsosym) | LC_ALL=C sort > $@

include/generated/bt-vdso-offsets.h: $(obj)/vdso.so.dbg FORCE
	$(call if_changed,vdsosym)

# actual build commands
# The DSO images are built using a special linker script
# Make sure only to export the intended __vdso_xxx symbol offsets.

quiet_cmd_vdsold = VDSOLD  $@
#      cmd_vdsold = $(LD) $(ld_flags) -T $(filter-out FORCE,$^) -o $@.tmp -L $(src) -lunicorn && \
#                   $(OBJCOPY) $(patsubst %, -G __vdso_%, $(vdso-syms)) $@.tmp $@ && \
#                   rm $@.tmp
#      cmd_vdsold = $(LD) $(ld_flags) -shared -Bsymbolic -warn-unresolved-symbols -T $(filter-out FORCE,$^) -o $@.tmp -L $(src) -lunicorn \
#                   -L /usr/riscv64-linux-gnu/lib -lc -lm \
#                   -L /usr/lib/gcc-cross/riscv64-linux-gnu/9 -latomic -lgcc && \
#                   $(OBJCOPY) $(patsubst %, -G __vdso_%, $(vdso-syms)) $@.tmp $@ && \
#                   rm $@.tmp
      cmd_vdsold = $(LD) -T $(filter-out FORCE,$^) $(ld_flags) -o $@.tmp && \
                   $(OBJCOPY) $(patsubst %, -G __vdso_%, $(vdso-syms)) $@.tmp $@ && \
                   rm $@.tmp

# install commands for the unstripped file
quiet_cmd_vdso_install = INSTALL $@
      cmd_vdso_install = cp $(obj)/$@.dbg $(MODLIB)/bt-vdso/$@

vdso.so: $(obj)/vdso.so.dbg
	@mkdir -p $(MODLIB)/bt-vdso
	$(call cmd,vdso_install)

vdso_install: vdso.so
