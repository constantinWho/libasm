global ft_strlen

section .text	; not doing much, just tells nasm that everything under is code(which is default anyway)

ft_strlen:
	xor rax, rax	;rax is what we return, in this case it is basically int i = 0;

.loop:
	cmp byte [rdi + rax], 0 ; s[i] == 0 ? 
	je .done ;je - jump if equal
	inc rax ; move
	jmp .loop

.done:
	ret

