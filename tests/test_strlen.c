#include "../include/libasm.h"

static void test_strlen_case(const char *str) {
	size_t ft_res = ft_strlen(str);
	size_t libc_res = strlen(str);
	if (ft_res == libc_res) {
		printf("%s✓%s ft_strlen(\"%s\") = %zu\n", GREEN, RESET,
			str ? str : "(null)", ft_res);
		g_tests_passed++;
	} else {
		printf("%s✗%s ft_strlen(\"%s\"): expected %zu, got %zu\n", RED, RESET,
			str ? str : "(null)", libc_res, ft_res);
		g_tests_failed++;
	}
}

void test_strlen(void) {
	print_header("TESTING FT_STRLEN");
	for (int i = 0; i < 12; i++) {
		test_strlen_case(test_cases[i]);
	}
}