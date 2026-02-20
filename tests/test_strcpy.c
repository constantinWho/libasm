#include "../include/libasm.h"

static void test_strcpy_case(const char *src) {
	char ft_dest[1024];
	char libc_dest[1024];
	char *ft_ret;
	char *libc_ret;
	
	ft_ret = ft_strcpy(ft_dest, src);
	libc_ret = strcpy(libc_dest, src);
	
	if (strcmp(ft_dest, libc_dest) == 0 && ft_ret == ft_dest && libc_ret == libc_dest) {
		printf("%s✓%s ft_strcpy(\"%s\") = \"%s\"\n", GREEN, RESET,
			src, ft_dest);
		g_tests_passed++;
	} else {
		printf("%s✗%s ft_strcpy(\"%s\"): expected \"%s\", got \"%s\"\n", RED, RESET,
			src, libc_dest, ft_dest);
		if (ft_ret != ft_dest) {
			printf("    (return value wrong: expected %p, got %p)\n", 
				(void*)ft_dest, (void*)ft_ret);
		}
		g_tests_failed++;
	}
}

void test_strcpy(void) {
	print_header("TESTING FT_STRCPY");
	for (int i = 0; i < 12; i++) {
		test_strcpy_case(test_cases[i]);
	}
}