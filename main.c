#include "libasm.h"

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

static void test_strcpy_case(const char *src) {
	char ft_dest[300];
	char libc_dest[300];

	ft_strcpy(ft_dest, src);
	strcpy(libc_dest, src);

	if (strcmp(ft_dest, libc_dest) == 0) {
		printf("%s✓%s ft_strcpy(\"%s\") = \"%s\"\n", GREEN, RESET,
			ft_dest, ft_dest);
		g_tests_passed++;
	} else {
		printf("%s✗%s ft_strcpy(\"%s\"): expected %s, got %s\n", RED, RESET,
			libc_dest, libc_dest, ft_dest);
		g_tests_failed++;
	}
}

static void test_strcmp_case_eq(const char *src) {
	int ft_res;
	int libc_res;

	ft_res = ft_strcmp(src, src);
	libc_res = strcmp(src, src);
	if (ft_res == libc_res) {
		printf("%s✓%s \"%s\"\n", GREEN, RESET, src);
		g_tests_passed++;
	} else {
		printf("%s✗%s ft_strcmp(\"%s\"): expected %d, got %d\n", RED, RESET,
			src, libc_res, ft_res);
		g_tests_failed++;
	}
}


static void test_strcmp_case_neq(const char *s1, const char *s2) {
	int ft_res;
	int libc_res;

	ft_res = ft_strcmp(s1, s2);
	libc_res = strcmp(s1, s2);
	printf("	s1: \"%s\", \n\ts2: \"%s\"\n", s1, s2);
	if (ft_res == libc_res) {
		printf("%s✓%s ft_strcmp: %d, strcmp: %d\n", GREEN, RESET, ft_res, libc_res);
		g_tests_passed++;
	} else {
		printf("%s✗%s expected %d, got %d\n", RED, RESET,
			libc_res, ft_res);
		g_tests_failed++;
	}
}

static void test_strlen(void) {
	print_header("TESTING FT_STRLEN");

	for (int i = 0; i < 12; i++) {
		test_strlen_case(test_cases[i]);
	}
}

static void test_strcpy(void) {
	print_header("TESTING FT_STRCPY");

	for (int i = 0; i < 12; i++) {
		test_strcpy_case(test_cases[i]);
	}
}

static void test_strcmp(void) {
	print_header("TESTING FT_STRCMP");

	printf("%ss1==s2%s\n\n", YELLOW, RESET);
	for (int i = 0; i < 12; i++) {
		test_strcmp_case_eq(test_cases[i]);
	}

	printf("\n%ss1!=s2%s\n\n", YELLOW, RESET);
	for (int i = 0; i < 12; i++) {
		test_strcmp_case_neq(test_cases[i], test_cases[(i == 11) ? 0 : (i + 1)]);
	}
}

int main(void) {
	print_start();
	test_strlen();
	test_strcpy();
	test_strcmp();
	print_end();
	return (g_tests_failed == 0) ? 0 : 1;
}
