#include "libasm.h"

void print_header(const char *title) {
	printf("\n%s========================================%s\n", BLUE, RESET);
	printf("%s             %s             %s\n", BLUE, title, RESET);
	printf("%s========================================%s\n\n", BLUE, RESET);
}

void print_test_result(void) {
	if (g_tests_failed > 0)
		printf("%sFailed: %d%s\n", RED, g_tests_failed, RESET);
	else
		printf("Failed: 0\n");
	if (g_tests_failed == 0)
		printf("\n%s🎉 All tests passed!%s\n\n", GREEN, RESET);
	else
		printf("\n%s⚠️  Some tests failed%s\n\n", YELLOW, RESET);
}

void print_end(void) {
	int total = g_tests_passed + g_tests_failed;

	printf("\n%s========================================%s\n", BLUE, RESET);
	printf("%s              TEST SUMMARY              %s\n", BLUE, RESET);
	printf("%s========================================%s\n", BLUE, RESET);
	printf("Total tests: %d\n", total);
	printf("%sPassed: %d%s\n", GREEN, g_tests_passed, RESET);
	print_test_result();
}

void print_start(void) {
	printf("\n%s╔═════════════════════════════════════════╗%s\n", BLUE, RESET);
	printf("%s║              LIBASM TESTER              ║%s\n", BLUE, RESET);
	printf("%s╚═════════════════════════════════════════╝%s\n", BLUE, RESET);
}

