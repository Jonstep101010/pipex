/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:41:45 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/18 17:17:20 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_files(t_input *input, char *infile, char *outfile)
{
	input->f1 = open(infile, O_RDONLY);
	if (input->f1 < 0)
		input->err_fd = ERR_FDO1;
	input->f2 = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input->f2 < 0)
	{
		if (input->err_fd != ERR_FDO1)
			input->err_fd = ERR_FDO2;
		free_and_exit(input, ERR_FDO2);
	}
}

void	parse_input(t_input *input)
{
	char	**tmp1;
	char	**tmp2;

	tmp1 = NULL;
	tmp2 = NULL;
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
	input->cmd2_args = arr_dup(tmp2);
	arr_free(tmp2);
}
