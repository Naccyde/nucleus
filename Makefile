SRC_S = src/boot/loader.s src/io/io.s src/mm/gdt.s
SRC_C = src/main.c src/video/vga.c src/lib/string.c src/io/serial.c src/debug.c \
	src/mm/gdt.c src/mm/idt.c
OBJ = $(SRC_S:%.s=build/%.s.o) $(SRC_C:%.c=build/%.c.o)
OBJ_DIR = $(dir $(OBJ))

AS = nasm
CC = gcc
LD = ld

ASFLAGS = -f elf
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -c -Isrc \
	-fdiagnostics-color=always -std=gnu11
LDFLAGS = -T src/boot/link.ld -melf_i386

all: nucleus

_setup:
	@mkdir -p $(OBJ_DIR)

nucleus: _setup $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o build/$@

build/nucleus.iso: nucleus
	mkdir -p build/iso/boot/grub
	cp resources/menu.lst build/iso/boot/grub
	cp resources/stage2_eltorito build/iso/boot/grub
	cp build/nucleus build/iso/boot/nucleus
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

run: build/nucleus.iso
	bochs -qf resources/bochsrc.txt

build/%.c.o: %.c
	$(CC) $(CFLAGS) $< -o $@

build/%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf `find build -name "*.o"` build/nucleus build/nucleus.iso

mrproper:
	rm -rf build