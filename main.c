#include "libasm.h"

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;36m"
#define RESET "\033[0m"

static int g_tests_passed = 0;
static int g_tests_failed = 0;

static void print_header(const char *title) {
	printf("\n%s========================================%s\n", BLUE, RESET);
	printf("%s  %s%s\n", BLUE, title, RESET);
	printf("%s========================================%s\n\n", BLUE, RESET);
}

static void test_strlen_case(const char *str) {
	size_t ft_result = ft_strlen(str);
	size_t libc_result = strlen(str);

	if (ft_result == libc_result) {
		printf("%s✓%s ft_strlen(\"%s\") = %zu\n", GREEN, RESET,
			str ? str : "(null)", ft_result);
		g_tests_passed++;
	} else {
		printf("%s✗%s ft_strlen(\"%s\"): expected %zu, got %zu\n", RED, RESET,
			str ? str : "(null)", libc_result, ft_result);
		g_tests_failed++;
	}
}

static void test_strlen(void) {
	print_header("TESTING FT_STRLEN");

	// Basic tests
	test_strlen_case("Hello, World!");
	test_strlen_case("test");
	test_strlen_case("");
	test_strlen_case("a");
	test_strlen_case("42");

	// Longer strings
	test_strlen_case("This is a longer string to test the function");
	test_strlen_case("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");

	// Special characters
	test_strlen_case("Hello\nWorld");
	test_strlen_case("Tab\there");
	test_strlen_case("Special chars: !@#$%^&*()");

	// Unicode/UTF-8 (byte count, not character count)
	test_strlen_case("Hello 世界");
	test_strlen_case("émojis: 🚀🔥");
}

static void print_summary(void) {
	int total = g_tests_passed + g_tests_failed;

	printf("\n%s========================================%s\n", BLUE, RESET);
	printf("%s  TEST SUMMARY%s\n", BLUE, RESET);
	printf("%s========================================%s\n", BLUE, RESET);
	printf("Total tests: %d\n", total);
	printf("%sPassed: %d%s\n", GREEN, g_tests_passed, RESET);
	if (g_tests_failed > 0)
		printf("%sFailed: %d%s\n", RED, g_tests_failed, RESET);
	else
		printf("Failed: 0\n");

	if (g_tests_failed == 0)
		printf("\n%s🎉 All tests passed!%s\n\n", GREEN, RESET);
	else
		printf("\n%s⚠️  Some tests failed%s\n\n", YELLOW, RESET);
}

int main(void) {
	printf("\n%s╔════════════════════════════════════════╗%s\n", BLUE, RESET);
	printf("%s║      LIBASM TESTER                     ║%s\n", BLUE, RESET);
	printf("%s╚════════════════════════════════════════╝%s\n", BLUE, RESET);

	test_strlen();

	print_summary();

	return (g_tests_failed == 0) ? 0 : 1;
}
