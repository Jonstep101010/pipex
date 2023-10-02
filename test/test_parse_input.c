#include "reqs.h"

void setUp(void){}
void tearDown(void){}

void test_parse_input(void)
{
	t_input input;
	char *argv[] = {"pipex", "infile.txt", "cmd1", "cmd2", "outfile.txt", NULL};
	parse_input(5, argv, &input);
	TEST_ASSERT_EQUAL_STRING("infile.txt", input.infile);
	TEST_ASSERT_EQUAL_STRING("cmd1", input.cmd1);
	TEST_ASSERT_EQUAL_STRING("cmd2", input.cmd2);
	TEST_ASSERT_EQUAL_STRING("outfile.txt", input.outfile);
}
