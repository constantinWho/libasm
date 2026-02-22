#include "../include/libasm.h"

static void test_strdup_case(const char *src) {
	char *ft_ret;
	char *libc_ret;

    if (!src) {
        ft_ret = ft_strdup(NULL);
        printf(ft_ret == NULL ? "%s✓%s ft_strdup(NULL) = NULL\n"
                              : "%s✗%s ft_strdup(NULL) should return NULL\n",
            ft_ret == NULL ? GREEN : RED, RESET);
        ft_ret == NULL ? g_tests_passed++ : g_tests_failed++;
        return ;
    }
	errno = 0;
	ft_ret = ft_strdup(src);
	int saved_errno_ft = errno;
	errno = 0;
	libc_ret = strdup(src);
	int saved_errno_libc = errno;

	if (ft_ret && libc_ret && strcmp(ft_ret, libc_ret) == 0 && saved_errno_ft == saved_errno_libc)
		printf("%s✓%s ft_strdup(\"%s\") = \"%s\"\n", GREEN, RESET, src, ft_ret);
	else if (!ft_ret && !libc_ret && saved_errno_ft == saved_errno_libc)
		printf("%s✓%s ft_strdup(NULL) = NULL, errno: %d\n", GREEN, RESET, saved_errno_ft);
	else {
		printf("%s✗%s ft_strdup(\"%s\"): expected \"%s\", got \"%s\"\n", RED, RESET,
			src, libc_ret, ft_ret);
		if (saved_errno_ft != saved_errno_libc)
			printf("    (errno wrong: expected %d, got %d)\n", saved_errno_libc, saved_errno_ft);
		g_tests_failed++;
		free(ft_ret);
		free(libc_ret);
		return ;
	}
	g_tests_passed++;
	free(ft_ret);
	free(libc_ret);
}

void test_strdup(void) {
	print_header("TESTING FT_STRDUP");
	for (int i = 0; i < 12; i++)
		test_strdup_case(test_cases[i]);
	test_strdup_case(NULL);
	printf("\n");
}