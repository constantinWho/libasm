#ifndef LIBASM_H
# define LIBASM_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;36m"
# define RESET "\033[0m"

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
#include <fcntl.h>
#include <errno.h>

// LIBASM FUNCS
size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);

// PRINT_UTILS
void print_header(const char *title);
void print_test_result(void);
void print_end(void);
void print_start(void);

// GLOBAL VARS
extern int g_tests_passed;
extern int g_tests_failed;
extern const char *test_cases[];

#endif
