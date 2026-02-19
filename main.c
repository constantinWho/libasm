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
	printf("\n%sedge cases%s\n\n", YELLOW, RESET);
	test_strcmp_case_neq("abc", "abcd");
	test_strcmp_case_neq("abcd", "abc");
	test_strcmp_case_neq("", "a");
	test_strcmp_case_neq("ABC", "abc");
}

static void test_write(void) {
	print_header("TESTING FT_WRITE");
	int ft_ret;
	int libc_ret;
	int saved_errno_ft;
	int saved_errno_libc;
	
	printf(YELLOW "\n[Test 1: Valid file descriptor]\n" RESET);
	for (int i = 0; i < 12; i++) {
		printf("  Case %d: ", i + 1);
		errno = 0;
		ft_ret = ft_write(1, test_cases[i], ft_strlen(test_cases[i]));
		saved_errno_ft = errno;
		errno = 0;
		libc_ret = write(1, test_cases[i], ft_strlen(test_cases[i]));
		saved_errno_libc = errno;
		if (ft_ret == libc_ret && saved_errno_ft == saved_errno_libc) {
			printf(GREEN "✓ PASSED" RESET " (returned %d)\n", ft_ret);
			g_tests_passed++;
		} else {
			printf(RED "✗ FAILED" RESET "\n");
			printf("    ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
			printf("    write:    ret=%d, errno=%d\n", libc_ret, saved_errno_libc);
			g_tests_failed++;
		}
	}
	
	printf(YELLOW "\n[Test 2: Invalid file descriptor (-1)]\n" RESET);
	errno = 0;
	ft_ret = ft_write(-1, "test", 4);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(-1, "test", 4);
	saved_errno_libc = errno;
	if (ft_ret == -1 && libc_ret == -1 && saved_errno_ft == saved_errno_libc) {
		printf(GREEN "✓ PASSED" RESET " (returned -1, errno=%d [EBADF])\n", saved_errno_ft);
		g_tests_passed++;
	} else {
		printf(RED "✗ FAILED" RESET "\n");
		printf("  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
		printf("  write:    ret=%d, errno=%d\n", libc_ret, saved_errno_libc);
		g_tests_failed++;
	}
	
	printf(YELLOW "\n[Test 3: Write 0 bytes]\n" RESET);
	errno = 0;
	ft_ret = ft_write(1, "test", 0);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(1, "test", 0);
	saved_errno_libc = errno;
	if (ft_ret == libc_ret && saved_errno_ft == saved_errno_libc) {
		printf(GREEN "✓ PASSED" RESET " (returned %d)\n", ft_ret);
		g_tests_passed++;
	} else {
		printf(RED "✗ FAILED" RESET "\n");
		printf("  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
		printf("  write:    ret=%d, errno=%d\n", libc_ret, saved_errno_libc);
		g_tests_failed++;
	}
	
	printf(YELLOW "\n[Test 4: NULL pointer]\n" RESET);
	errno = 0;
	ft_ret = ft_write(1, NULL, 5);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(1, NULL, 5);
	saved_errno_libc = errno;
	if (ft_ret == -1 && libc_ret == -1 && saved_errno_ft == saved_errno_libc) {
		printf(GREEN "✓ PASSED" RESET " (returned -1, errno=%d [EFAULT])\n", saved_errno_ft);
		g_tests_passed++;
	} else {
		printf(RED "✗ FAILED" RESET "\n");
		printf("  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
		printf("  write:    ret=%d, errno=%d\n", libc_ret, saved_errno_libc);
		g_tests_failed++;
	}
	
	printf(YELLOW "\n[Test 5: Closed file descriptor]\n" RESET);
	int fd = open("/tmp/test_ft_write", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
	errno = 0;
	ft_ret = ft_write(fd, "test", 4);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(fd, "test", 4);
	saved_errno_libc = errno;
	if (ft_ret == -1 && libc_ret == -1 && saved_errno_ft == saved_errno_libc) {
		printf(GREEN "✓ PASSED" RESET " (returned -1, errno=%d [EBADF])\n", saved_errno_ft);
		g_tests_passed++;
	} else {
		printf(RED "✗ FAILED" RESET "\n");
		printf("  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
		printf("  write:    ret=%d, errno=%d\n", libc_ret, saved_errno_libc);
		g_tests_failed++;
	}
	unlink("/tmp/test_ft_write");
	
	printf(YELLOW "\n[Test 6: Large write (10000 bytes)]\n" RESET);
	char *large_buf = malloc(10000);
	memset(large_buf, 'A', 10000);
	int pipefd[2];
	pipe(pipefd);
	errno = 0;
	ft_ret = ft_write(pipefd[1], large_buf, 10000);
	saved_errno_ft = errno;
	char drain[10000];
	read(pipefd[0], drain, 10000);
	errno = 0;
	libc_ret = write(pipefd[1], large_buf, 10000);
	saved_errno_libc = errno;
	close(pipefd[0]);
	close(pipefd[1]);
	free(large_buf);
	if (ft_ret == libc_ret && saved_errno_ft == saved_errno_libc) {
		printf(GREEN "✓ PASSED" RESET " (returned %d)\n", ft_ret);
		g_tests_passed++;
	} else {
		printf(RED "✗ FAILED" RESET "\n");
		printf("  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
		printf("  write:    ret=%d, errno=%d\n", libc_ret, saved_errno_libc);
		g_tests_failed++;
	}
	printf("\n");
}

int main(void) {
	print_start();
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	print_end();
	return (g_tests_failed == 0) ? 0 : 1;
}