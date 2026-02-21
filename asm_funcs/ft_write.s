global ft_write

extern __errno_location

section .text

ft_write:
    mov rax, 1 ;write args are already directly moved fd to rdi, but to rsi, count to rdx
	syscall ; kernel returns values into rax after execution 
	cmp rax, 0
	jl .error ;jump if less than zero
	ret

.error:
	neg rax ;beacause kernel has returned a negative value, we have to make it positive
	push rax ;saving the value on the stack so it does not get overwritten
	call __errno_location wrt ..plt ;wrt = with respect to, ..plt = procedures linkage table
	pop rcx
	mov [rax], rcx 
	mov rax, -1
	ret

