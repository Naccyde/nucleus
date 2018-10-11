; Set symbols visible outside
global outb
global inb

; outb - Send a byte to an I/O port
; stack: [esp + 8] data byte
;	 [esp + 4] I/O port
;	 [esp    ] Return address
outb:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

; inb - Read a byte from an I/O port
; stack: [esp + 4] I/O port
;	 [esp    ] Return address
inb:
	mov dx, [esp + 4]
	in al, dx
	ret
