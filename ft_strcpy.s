global ft_strcpy

section .text

ft_strcpy:
	mov rax, rdi
	xor rcx, rcx

.loop:
	mov cl, [rsi]
	mov [rdi], cl
	inc rsi
	inc rdi
	test cl, cl
	jnz .loop
	ret
