global ft_strcpy

section .text

ft_strcpy:
	mov rax, rdi ;moving the adress of dest to rax
	xor rcx, rcx ;counter reset to 0

.loop:
	mov cl, [rsi] ;move 1 byte from current position to tmp cl
	mov [rdi], cl ;move 1 byte from tmp to dest
	inc rsi ;point to next char in src
	inc rdi ;point to next char in dest
	cmp cl, 0 ;check the null terminator
	jne .loop
	ret
