#include "../include/libasm.h"

int g_tests_passed = 0;
int g_tests_failed = 0;

const char *test_cases[] = {
	// Basic tests
	"Hello, World!",
	"test",
	"",
	"a",
	"42",
	// Longer strings
	"This is a longer string to test the function",
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
	// Special characters
	"Hello\nWorld",
	"Tab\there",
	"Special chars: !@#$%^&*()",
	// Unicode/UTF-8 (byte count, not character count)
	"Hello 世界",
	"émojis: 🚀🔥",
	NULL
};
