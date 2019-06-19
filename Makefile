PWD = $(shell pwd)
BUILD_DIR = $(PWD)/build
ROOT_DIR = $(BUILD_DIR)/root

SRC_S = nucleus/boot/loader.s nucleus/io/io.s nucleus/cpu/gdt.s \
	nucleus/cpu/int/isr.s nucleus/cpu/int/idt.s nucleus/mm/paging.s
SRC_C = nucleus/main.c nucleus/video/vga.c nucleus/io/serial.c \
	nucleus/debug.c nucleus/cpu/gdt.c nucleus/cpu/int/idt.c \
	nucleus/cpu/int/isr.c nucleus/cpu/int/irq.c nucleus/io/kb.c \
	nucleus/io/io.c nucleus/cpu/timer.c nucleus/mm/paging.c \
	nucleus/mm/alloc.c nucleus/mm/frames_bitset.c nucleus/mm/pmm.c \
	nucleus/lib/string.c nucleus/lib/stdlib.c
OBJ = $(SRC_S:%.s=build/%.s.o) $(SRC_C:%.c=build/%.c.o)
OBJ_DIR = $(dir $(OBJ))

AS = nasm
CC = gcc
LD = ld
BOCHS=$(ROOT_DIR)/bin/bochs

ASFLAGS = -f elf -g
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -c -Isrc \
	-fdiagnostics-color=always -std=gnu11 -Wno-pointer-sign \
	-Iinclude -g -O0
LDFLAGS = -T nucleus/boot/link.ld -melf_i386

all: nucleus

.PHONY: nucleus

_setup:
	@mkdir -p $(OBJ_DIR) $(LIB_OBJ_DIR)

nucleus: _setup $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o build/$@.bin

iso: nucleus
	mkdir -p build/iso/boot/grub
	cp resources/menu.lst build/iso/boot/grub
	cp resources/stage2_eltorito build/iso/boot/grub
	cp build/nucleus.bin build/iso/boot/nucleus
	genisoimage -R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-input-charset utf8 \
		-quiet \
		-boot-info-table \
		-o build/nucleus.iso \
		build/iso

run: iso
	ROOT_DIR=$(ROOT_DIR) BUILD_DIR=$(BUILD_DIR) LTDL_LIBRARY_PATH=$(ROOT_DIR)/lib/bochs/plugins $(BOCHS) -qf $(PWD)/resources/bochsrc.txt

build/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build/%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

bochs: _setup
	mkdir -p build/root && \
	cd build && \
	git clone https://github.com/callcc/bochs.git && \
	cd bochs && \
	./configure --with-sdl2 --enable-plugins --enable-gdb-stub \
		--enable-disasm --enable-show-ips \
		--enable-x86-debugger --enable-repeat-speedups \
		--prefix=$(PWD)/build/root && \
	$(MAKE) install

clean:
	rm -rf `find build -name "*.o"` build/nucleus.bin build/nucleus.iso || true

mrproper:
	rm -rf build || true
