NAME		= libasm.a
CC			= cc
NASM		= nasm
NASMFLAGS	= -f elf64
CFLAGS		= -Wall -Wextra -Werror

SRCS		= ft_strlen.s ft_strcpy.s

OBJS		= $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

test: $(NAME)
	$(CC) $(CFLAGS) main.c -L. -lasm -o test
	./test

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re test
