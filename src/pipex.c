/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:47:28 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/13 16:43:58 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(int argc, char **argv, t_input *input)
{
	int	i;

	i = 1;
	if (argc < 3)
		exit(EXIT_FAILURE);
	while (i < argc && argv[i])
		i++;
	*input = (t_input)
	{
		.args = i,
		.infile = argv[1],
		.cmd1 = argv[2],
		.cmd2 = argv[3],
		.outfile = argv[4],
	};
	printf("%s\n", input->infile);
	printf("%s\n", input->cmd1);
	printf("%s\n", input->cmd2);
	printf("%s\n", input->outfile);
}
	// if (!input->outfile)
	// 	print_stdout()//pipes both commands like: < infile.txt grep test | wc -c
	// if (!input->outfile && !input->cmd2)
	// 	pipe_open()//pipe cli or just print cmd1 and infile output

/*
pipes by default cause direction to shell -> command not found

non existing files need to be created

if no outfile specified, write to stdout
*/
/**
 * @param argc
 * @param argv
 * @param ENV environment to parse @todo
 * @return int EXITCODE
 */
int	main(int argc, char **argv, char **ENV)
{
	t_program	pipex;

	if (argc <= 2 && argv[1])
		return (print_file_contents(argv[1]), EXIT_SUCCESS);
	parse_input(argc, argv, &(pipex.input));
	(void)argc;
	(void)argv;
	(void)ENV;
	return (EXIT_SUCCESS);
}
