NAME		= libasm.a
CC			= cc
NASM		= nasm
NASMFLAGS	= -f elf64
CFLAGS		= -Wall -Wextra -Werror -g
NOPIE		= -no-pie #Just means that the assigment of memory would be liniar
SRCS		= ./asm_funcs/ft_strlen.s ./asm_funcs/ft_strcpy.s \
			./asm_funcs/ft_strcmp.s ./asm_funcs/ft_write.s \
			./asm_funcs/ft_read.s ./asm_funcs/ft_strdup.s

OBJS		= $(SRCS:.s=.o)
TEST_OBJS	= main.c \
			./utils/global.c ./utils/print_utils.c \
			./tests/test_strlen.c \
			./tests/test_strcpy.c \
			./tests/test_strcmp.c \
			./tests/test_write.c \
			./tests/test_read.c \
			./tests/test_strdup.c

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