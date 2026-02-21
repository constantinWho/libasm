#include "../include/libasm.h"

static void valid_fd_test_read(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	printf("%svalid fd%s\n\n", YELLOW, RESET);
	for (int i = 0; i < 12; i++) {
		int pipefd[2];
		char ft_buf[1024];
		char libc_buf[1024];
		memset(ft_buf, 0, 1024);
		memset(libc_buf, 0, 1024);

		pipe(pipefd);
		write(pipefd[1], test_cases[i], ft_strlen(test_cases[i]));
		errno = 0;
		ft_ret = ft_read(pipefd[0], ft_buf, ft_strlen(test_cases[i]));
		saved_errno_ft = errno;
		close(pipefd[0]);
		close(pipefd[1]);

		pipe(pipefd);
		write(pipefd[1], test_cases[i], ft_strlen(test_cases[i]));
		errno = 0;
		libc_ret = read(pipefd[0], libc_buf, ft_strlen(test_cases[i]));
		saved_errno_libc = errno;
		close(pipefd[0]);
		close(pipefd[1]);

		printf("\tft_read:  \"%s\"\n", ft_buf);
		printf("\tread:     \"%s\"\n", libc_buf);
		if (ft_ret == libc_ret && saved_errno_ft == saved_errno_libc) {
			printf("%s✓%s ft_ret: %d, libc_ret: %d\n\n", GREEN, RESET, ft_ret, libc_ret);
			g_tests_passed++;
		} else {
			printf("%s✗%s\n", RED, RESET);
			printf("\t  ft_read: ret=%d, errno=%d\n", ft_ret, saved_errno_ft);
			printf("\t  read:    ret=%d, errno=%d\n\n", libc_ret, saved_errno_libc);
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

static void neg_fd_test_read(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	char buf[10];
	errno = 0;
	ft_ret = ft_read(-1, buf, 10);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = read(-1, buf, 10);
	saved_errno_libc = errno;
	run_test("fd == -1", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 1);
}

static void read_zero_bytes_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	int pipefd[2];
	char buf[10];
	pipe(pipefd);
	write(pipefd[1], "test", 4);
	errno = 0;
	ft_ret = ft_read(pipefd[0], buf, 0);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = read(pipefd[0], buf, 0);
	saved_errno_libc = errno;
	close(pipefd[0]);
	close(pipefd[1]);
	run_test("read 0 bytes", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 0);
}

static void null_ptr_test_read(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	int pipefd[2];
	pipe(pipefd);
	write(pipefd[1], "test", 4);
	errno = 0;
	ft_ret = ft_read(pipefd[0], NULL, 5);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = read(pipefd[0], NULL, 5);
	saved_errno_libc = errno;
	close(pipefd[0]);
	close(pipefd[1]);
	run_test("NULL pointer", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 1);
}

static void closed_fd_test_read(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	int pipefd[2];
	char buf[10];
	pipe(pipefd);
	close(pipefd[0]);
	errno = 0;
	ft_ret = ft_read(pipefd[0], buf, 10);
	saved_errno_ft = errno;
	errno = 0;
	libc_ret = read(pipefd[0], buf, 10);
	saved_errno_libc = errno;
	close(pipefd[1]);
	run_test("closed fd", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 1);
}

static void large_read_test(int ft_ret, int saved_errno_ft,
					int libc_ret, int saved_errno_libc) {
	char *large_buf = malloc(10000);
	char ft_buf[10000];
	char libc_buf[10000];
	memset(large_buf, 'A', 10000);
	memset(ft_buf, 0, 10000);
	memset(libc_buf, 0, 10000);

	int pipefd[2];
	pipe(pipefd);
	write(pipefd[1], large_buf, 10000);
	errno = 0;
	ft_ret = ft_read(pipefd[0], ft_buf, 10000);
	saved_errno_ft = errno;
	close(pipefd[0]);
	close(pipefd[1]);

	pipe(pipefd);
	write(pipefd[1], large_buf, 10000);
	errno = 0;
	libc_ret = read(pipefd[0], libc_buf, 10000);
	saved_errno_libc = errno;
	close(pipefd[0]);
	close(pipefd[1]);

	free(large_buf);
	run_test("large read (10000 bytes)", ft_ret, saved_errno_ft, libc_ret, saved_errno_libc, 0);
}

void test_read(void) {
	int ft_ret = 0;
	int libc_ret = 0;
	int saved_errno_ft = 0;
	int saved_errno_libc = 0;

	print_header("TESTING FT_READ");
	valid_fd_test_read(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	neg_fd_test_read(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	read_zero_bytes_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	null_ptr_test_read(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	closed_fd_test_read(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	large_read_test(ft_ret, saved_errno_ft, libc_ret, saved_errno_libc);
	printf("\n");
}