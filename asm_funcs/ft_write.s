global ft_write

extern __errno_location

section .text

ft_write:
    mov rax, 1
	syscall
	test rax, rax
	js .error
	ret

.error:
	neg rax
	push rax
	call __errno_location wrt ..plt
	pop rcx
	mov [rax], rcx 
	mov rax, -1
	ret

