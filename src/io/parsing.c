/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/17 21:49:11 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_input *input, char *infile, char *outfile)
{
	input->f1 = open(infile, O_RDONLY);
	if (input->f1 < 0)
		free_and_exit(input, EXIT_SUCCESS);
	input->f2 = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input->f2 < 0)
		free_and_exit(input, EXIT_SUCCESS);
}

//@todo make sure exit is appropriate for case handling
//@follow-up handle "here_doc"
void	parse_input(t_input *input)
{
	char	**tmp1;
	char	**tmp2;

	open_files(input, input->av[1], input->av[input->ac - 1]);
	tmp1 = parse_args(input->av[2]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		return (free_and_exit(input, EXIT_FAILURE));
	input->cmd1 = ft_strdup(tmp1[0]);
	input->cmd1_args = tmp1;
	tmp2 = parse_args(input->av[input->ac - 2]);
	if (!tmp2 || !*tmp2 || !**tmp2)
		return (free_and_exit(input, EXIT_FAILURE));
	input->cmd2 = ft_strdup(tmp2[0]);
	input->cmd2_args = tmp2;
}
	// input->infile = input->av[1];
	// input->f1 = open(input->infile, O_RDONLY);
	// if (input->f1 < 0)
	// 	free_and_exit(input, EXIT_SUCCESS);
	// input->outfile = input->av[input->ac - 1];
	// input->f2 = open(input->outfile, O_CREAT | O_RDWR | O_TRUNC, 0644)