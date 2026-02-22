#include "./include/libasm.h"

int main(void) {
	print_start();
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	print_end();
	return (g_tests_failed == 0) ? 0 : 1;
}