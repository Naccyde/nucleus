VERSION=0.0.1

AS=nasm
CC=gcc
ASFLAGS=-f elf32
CFLAGS=-m32 -Wall -Wextra -std=c11
LDFLAGS=-m elf_i386 -T src/boot/link.ld
EXEC=nucleus

SRC = src/kernel.c
OBJ = $(patsubst %.c,build/%.o,$(SRC))


.PHONY: $(EXEC) boot clean mrproper

all: _prepare $(EXEC)

_prepare:
	@mkdir -p build

$(EXEC): boot $(OBJ)
	$(LD) $(LDFLAGS) build/boot.o $(OBJ) -o build/$(EXEC)

boot:
	$(AS) $(ASFLAGS) src/boot/boot.asm -o build/boot.o

build/src/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

test: $(EXEC)
	qemu-system-i386 -kernel build/$(EXEC)

clean:
	rm -rf build/$(EXEC)

mrproper:
	rm -rf build
