#include "reqs.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ft_strlen_should_return_same_as_strlen(void)
{
    char *str = "Hello World!";
    TEST_ASSERT_EQUAL_INT(strlen(str), ft_strlen(str));
    char *str2 = "";
    TEST_ASSERT_EQUAL_INT(strlen(str2), ft_strlen(str2));
}
