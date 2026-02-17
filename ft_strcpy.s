global ft_strcpy

section .text

ft_strcpy:
	mov rax, rdi
	xor rcx, rcx

.loop
	movzx rdx, byte [rsi + rcx]
	mov [rdi + rcx], dl
	inc rcx
	test dl, dl
	jnz .loop

.done:
	ret
