global ft_strdup

extern malloc
extern ft_strlen
extern ft_strcpy

section .text

ft_strdup:
    cmp rdi, rdi
    cmp rdi, 0
    je .null
    push rbx                ; will be storing the amount of bytes needed
    push r12                ; will be storing the adress of src
    mov r12, rdi            ; r12 now points to src string
    call ft_strlen          ; rax = length of src
    inc rax                 ; include null terminator
    mov rdi, rax            ; now rdi will become arg for malloc
    call malloc wrt ..plt
    cmp rax, 0
    je .fail
    mov rbx, rax            ; save malloc result
    mov rdi, rax            ; dst
    mov rsi, r12            ; src
    call ft_strcpy
    mov rax, rbx            ; return original malloc pointer
    jmp .done
.fail:
    xor rax, rax
    jmp .done
.null:
    xor rax, rax
    ret
.done:
    pop r12
    pop rbx
    ret