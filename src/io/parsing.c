/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/07 19:09:43 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(int argc, char **argv, t_input *input)
{
	char	**tmp1;
	char	**tmp2;

	if (argc < 5)
		free_and_exit(input, EXIT_FAILURE);
	while (input->args < argc && argv[input->args])
		input->args++;
	input->infile = argv[1];
	input->f1 = open(input->infile, O_RDONLY);
	if (input->f1 < 0)
		free_and_exit(input, EXIT_SUCCESS);
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
	input->outfile = argv[4];
	input->f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
}
