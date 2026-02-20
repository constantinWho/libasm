#include "../include/libasm.h"

void test_write(void) {
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
