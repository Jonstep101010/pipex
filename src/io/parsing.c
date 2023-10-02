/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/02 10:47:04 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(int argc, char **argv, t_input *input)
{
	input->args = 0;
	if (argc < 3)
		exit(EXIT_FAILURE);
	while (input->args < argc && argv[input->args])
		input->args++;
	*input = (t_input)
	{
		.infile = argv[1],
		.f1 = open(argv[1], O_RDONLY),
		.cmd1 = ft_split(argv[2], ' ')[0],
		.cmd2 = ft_split(argv[3], ' ')[0],
		.outfile = argv[4],
		.f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644),
	};
	if (input->f1 < 0 || input->f2 < 0)
		exit(EXIT_FAILURE);
	if (argv[2])
		input->cmd1_args = ft_split(argv[2], ' ');
	if (argv[3])
		input->cmd2_args = ft_split(argv[3], ' ')[1];
}

	// printf("%s\n", input->infile);
	// printf("%s\n", input->cmd1);
	// printf("%s\n", input->cmd1_args);
	// printf("%s\n", input->cmd2);
	// printf("%s\n", input->cmd2_args);
	// printf("%s\n", input->outfile);
