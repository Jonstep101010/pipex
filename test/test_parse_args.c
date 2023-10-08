#include "unity.h"
#include "parse_args.h"
#define TEST_SUITE "test_parse_args"
char	**g_ret;
void	test_workswith_singlequotes()
{
	g_ret = parse_args("awk '{count++} END {print count}'");
	char	*const exp[] = {"awk", "{count++} END {print count}", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(exp, g_ret, 2);
	arr_free(g_ret);
}

void	test_handles_multipleargs()
{
	g_ret = parse_args("ls -l -a");
	char	*const exp3[] = {"ls", "-l", "-a", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(exp3, g_ret, 3);
	arr_free(g_ret);
}

void	test_handles_simpleinput()
{
	g_ret = parse_args("grep test");
	char	*const exp2[] = {"grep", "test", NULL};
	TEST_ASSERT_EQUAL_STRING_ARRAY(exp2, g_ret, 2);
	arr_free(g_ret);
}
void	ignore_test_parse_args()
{
	test_handles_multipleargs();
	test_handles_simpleinput();
	test_workswith_singlequotes();
}
