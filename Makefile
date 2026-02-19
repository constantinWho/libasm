NAME		= libasm.a
CC			= cc
NASM		= nasm
NASMFLAGS	= -f elf64
CFLAGS		= -Wall -Wextra -Werror -g
NOPIE		= -no-pie

SRCS		= ft_strlen.s ft_strcpy.s ft_strcmp.s

OBJS		= $(SRCS:.s=.o)

TEST_OBJS	= global.c print_utils.c main.c

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

test: $(NAME)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. -lasm $(NOPIE) -o test
	./test

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) test

re: fclean all

.PHONY: all clean fclean re test
