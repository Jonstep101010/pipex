#include "unity.h"
#include "reqs.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void	test_parse_args(void)
{
	char	**ret;
	ret = NULL;
	ret = separate_cmd_args("awk '{count++} END {print count}'");
	TEST_ASSERT_EQUAL_STRING("awk", ret[0]);
	TEST_ASSERT_EQUAL_STRING("{count++} END {print count}", ret[1]);
	// arr_free(ret);
	// ret = NULL;
	// ret = separate_cmd_args("awk '{count++} END {print count}'");
}
