#include "unity.h"
#include "libft.h"

void setUp(void)
{
}

void tearDown(void)
{
}

# include <stdio.h>
void test_ft_printf_should_print_string(void)
{
    char *str = "Hello World!";
    TEST_ASSERT_EQUAL(12, ft_printf("%s", str));
    char *str2 = "";
    TEST_ASSERT_EQUAL(0, ft_printf("%s", str2));
}
