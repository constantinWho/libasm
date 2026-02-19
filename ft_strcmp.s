global ft_strcmp

section .text

ft_strcmp:
	xor rcx, rcx

.loop:
;could have used movzx which have had reseted the registers to zero
	xor rax, rax ;reset rax to 0
	xor rdx, rdx ;reset rdx to 0
	mov al, byte [rdi + rcx] ;moving 1 byte from s1
	mov dl, byte [rsi + rcx] ;moving 1 byte from s2
	cmp rax, rdx
	jne .diff ;if compared bytes are different we jump to the end
	cmp rax, 0 ;check if dest[i] == 0
	je .equal
	inc rcx
	jmp .loop

.diff:
	sub rax, rdx
	ret

.equal:
	xor rax, rax
	ret

