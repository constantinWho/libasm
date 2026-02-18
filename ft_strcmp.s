global ft_strcmp

section .text

ft_strcmp:
	xor rax, rax

.loop:
	cmp byte [rdi + rax], [rsi + rax]


