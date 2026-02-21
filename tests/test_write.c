#include "../include/libasm.h"

static void valid_fd_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	printf("%sfd == 1%s\n\n", YELLOW, RESET);
	for (int i = 0; i < 12; i++) {
		errno = 0;
		write(1, "\tft_write: \"", 12);
		ft_ret = ft_write(1, test_cases[i], ft_strlen(test_cases[i]));
		saved_errno_ft = errno;
		errno = 0;
		write(1, "\"\n\twrite:    \"", 13);
		libc_ret = write(1, test_cases[i], ft_strlen(test_cases[i]));
		saved_errno_libc = errno;
		write(1, "\"\n", 2);
		if (ft_ret == libc_ret && saved_errno_ft == saved_errno_libc) {
			printf("%s✓%s ft_ret: %d, libc_ret: %d\n\n", GREEN, RESET, ft_ret, libc_ret);
			g_tests_passed++;
		} else {
			printf("%s✗%s\n", RED, RESET);
			printf("\t  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
			printf("\t  write:    ret=%d, errno=%d\n\n", libc_ret, saved_errno_libc);
			g_tests_failed++;
		}
	}
}

static void run_test(const char *label, int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc, int expect_neg_one) {
	printf("%s%s%s\n", YELLOW, label, RESET);
	if (expect_neg_one) {
		if (ft_ret == -1 && libc_ret == -1 && saved_errno_ft == saved_errno_libc) {
			printf("%s✓%s ft_ret: %d, errno: %d | libc_ret: %d, errno: %d\n\n",
				GREEN, RESET, ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
			g_tests_passed++;
		} else {
			printf("%s✗%s\n", RED, RESET);
			printf("\t  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
			printf("\t  write:    ret=%d, errno=%d\n\n", libc_ret, saved_errno_libc);
			g_tests_failed++;
		}
	} else {
		if (ft_ret == libc_ret && saved_errno_ft == saved_errno_libc) {
			printf("%s✓%s ft_ret: %d, libc_ret: %d\n\n",
				GREEN, RESET, ft_ret, libc_ret);
			g_tests_passed++;
		} else {
			printf("%s✗%s\n", RED, RESET);
			printf("\t  ft_write: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
			printf("\t  write:    ret=%d, errno=%d\n\n", libc_ret, saved_errno_libc);
			g_tests_failed++;
		}
	}
}

static void neg_fd_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	errno = 0;
	ft_ret = ft_write(-1, "test", 4);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(-1, "test", 4);
	saved_errno_libc = errno;
	run_test("fd == -1", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 1);
}

static void write_zero_bytes_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	errno = 0;
	ft_ret = ft_write(1, "test", 0);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(1, "test", 0);
	saved_errno_libc = errno;
	run_test("write 0 bytes", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 0);
}

static void null_ptr_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	errno = 0;
	ft_ret = ft_write(1, NULL, 5);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(1, NULL, 5);
	saved_errno_libc = errno;
	run_test("NULL pointer", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 1);
}

static void closed_fd_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	int fd = open("/tmp/test_ft_write", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
	errno = 0;
	ft_ret = ft_write(fd, "test", 4);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = write(fd, "test", 4);
	saved_errno_libc = errno;
	run_test("closed fd", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 1);
	unlink("/tmp/test_ft_write");
}

static void large_write_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
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
	run_test("large write (10000 bytes)", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 0);
}

void test_write(void) {
	int ft_ret = 0;
	int libc_ret = 0;
	int saved_errno_ft = 0;
	int saved_errno_libc = 0;
	
	print_header("TESTING FT_WRITE");
	valid_fd_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	neg_fd_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	write_zero_bytes_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	null_ptr_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	closed_fd_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	large_write_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);

	printf("\n");
}