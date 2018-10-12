SRC_S = nucleus/boot/loader.s nucleus/io/io.s nucleus/mm/gdt.s \
	nucleus/mm/int/isr.s nucleus/mm/int/idt.s
SRC_C = nucleus/main.c nucleus/video/vga.c nucleus/io/serial.c \
	nucleus/debug.c nucleus/mm/gdt.c nucleus/mm/int/idt.c \
	nucleus/mm/int/isr.c nucleus/mm/int/irq.c nucleus/io/kb.c \
	nucleus/io/io.c nucleus/cpu/timer.c \
	nucleus/lib/string.c
OBJ = $(SRC_S:%.s=build/%.s.o) $(SRC_C:%.c=build/%.c.o)
OBJ_DIR = $(dir $(OBJ))

AS = nasm
CC = gcc
LD = ld
BOCHS=./resources/bochs/bin/bochs

ASFLAGS = -f elf
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
	LTDL_LIBRARY_PATH=resources/bochs/lib/bochs/plugins $(BOCHS) -qf resources/bochsrc.txt

build/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build/%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf `find build -name "*.o"` build/nucleus.bin build/nucleus.iso || true

mrproper:
	rm -rf build || true
