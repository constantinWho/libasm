#include "../include/libasm.h"

static void test_strcmp_case_eq(const char *src) {
	int ft_res;
	int libc_res;
	int ft_sign;
	int libc_sign;
	
	ft_res = ft_strcmp(src, src);
	libc_res = strcmp(src, src);
	
	ft_sign = (ft_res > 0) ? 1 : (ft_res < 0) ? -1 : 0;
	libc_sign = (libc_res > 0) ? 1 : (libc_res < 0) ? -1 : 0;
	
	printf("\ts1: \"%s\" \n\ts2: \"%s\"\n", src, src);
	if (ft_sign == libc_sign) {
		printf("%s✓%s ft_strcmp: %d, strcmp: %d\n", GREEN, RESET, ft_res, libc_res);
		g_tests_passed++;
	} else {
		printf("%s✗%s sign mismatch: ft=%d, libc=%d\n", RED, RESET,
			ft_sign, libc_sign);
		g_tests_failed++;
	}
}

static void test_strcmp_case_neq(const char *s1, const char *s2) {
	int ft_res;
	int libc_res;
	int ft_sign;
	int libc_sign;
	
	ft_res = ft_strcmp(s1, s2);
	libc_res = strcmp(s1, s2);
	
	ft_sign = (ft_res > 0) ? 1 : (ft_res < 0) ? -1 : 0;
	libc_sign = (libc_res > 0) ? 1 : (libc_res < 0) ? -1 : 0;
	
	printf("\ts1: \"%s\", \n\ts2: \"%s\"\n", s1, s2);
	if (ft_sign == libc_sign) {
		printf("%s✓%s ft_strcmp: %d, strcmp: %d\n", GREEN, RESET, ft_res, libc_res);
		g_tests_passed++;
	} else {
		printf("%s✗%s sign mismatch: ft=%d, libc=%d\n", RED, RESET,
			ft_sign, libc_sign);
		g_tests_failed++;
	}
}

void test_strcmp(void) {
	print_header("TESTING FT_STRCMP");
	printf("%ss1==s2%s\n\n", YELLOW, RESET);
	for (int i = 0; i < 12; i++) {
		test_strcmp_case_eq(test_cases[i]);
	}
	printf("\n%ss1!=s2%s\n\n", YELLOW, RESET);
	for (int i = 0; i < 12; i++) {
		test_strcmp_case_neq(test_cases[i], test_cases[(i == 11) ? 0 : (i + 1)]);
	}
	printf("\n%sedge cases%s\n\n", YELLOW, RESET);
	test_strcmp_case_neq("abc", "abcd");
	test_strcmp_case_neq("abcd", "abc");
	test_strcmp_case_neq("", "a");
	test_strcmp_case_neq("ABC", "abc");
}
