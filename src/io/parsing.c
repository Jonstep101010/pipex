/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/09 10:11:40 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// #define s_files struct s_files
// s_files	parse_fd(t_input *input)
// {
// 	s_files	files;

// 	files.fd1 = -1;
// 	files.fd2 = -1;
// 	files.infile = NULL;
// 	files.outfile = NULL;
// 	files.error = NULL;

// 	files.infile = input->argv[1];
// 	files.fd1 = open(files.infile, O_RDONLY);
// 	if (files.fd1 < 0 || !files.infile)
// 		free_and_exit(input, STDOUT_FILENO);

// 	files.fd2 = open(input->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	if (files.fd2 < 0)
// 		free_and_exit(input, 0);
// 	return (files);
// }

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(int argc, char **argv, t_input *input)
{
	char	**tmp1;
	char	**tmp2;

	if (argc < 5)
		free_and_exit(input, EXIT_FAILURE);

	input->argv = argv;
	input->args = argc;
	// parse_fd(input);
	// while (input->args < argc && argv[input->args])
	// 	input->args++;

	input->infile = argv[1];
	input->f1 = open(input->infile, O_RDONLY);
	if (input->f1 < 0)
		free_and_exit(input, EXIT_SUCCESS);
	input->outfile = argv[argc - 1];
	input->f2 = open(input->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	tmp1 = parse_args(argv[2]);
	if (!tmp1 || !tmp1[0])
		free_and_exit(input, EXIT_FAILURE);
	input->cmd1 = ft_strdup(tmp1[0]);
	input->cmd1_args = tmp1;
	tmp2 = parse_args(argv[3]);
	if (!tmp2 || !*tmp2)
		free_and_exit(input, EXIT_FAILURE);
	input->cmd2 = ft_strdup(tmp2[0]);
	input->cmd2_args = tmp2;
}
