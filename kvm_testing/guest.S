# as -32 guest.S -o guest.o 
# ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x10000 -o guest guest.o 
.globl _start
.code16
_start:
  xorw %ax, %ax
  movw 0x10, %cx
loop:
	out %ax, $0x10
	inc %ax
	dec %cx
	cmp %cx, 0x0
	je loop
