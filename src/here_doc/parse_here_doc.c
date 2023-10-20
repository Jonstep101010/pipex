/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:39:12 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/20 18:08:05 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_here_doc(t_input *input)
{
	char	**tmp1;

	input->f1 = STDIN_FILENO;
	tmp1 = parse_args(input->av[3]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		free_and_exit(input, EXIT_FAILURE);
	input->cmd1 = ft_strdup(tmp1[0]);
	input->cmd1_args = arr_dup(tmp1);
	arr_free(tmp1);
	tmp1 = parse_args(input->av[4]);
	if (!tmp1 || !*tmp1 || !**tmp1)
		free_and_exit(input, EXIT_FAILURE);
	input->cmd2 = ft_strdup(tmp1[0]);
	input->cmd2_args = arr_dup(tmp1);
	arr_free(tmp1);
	input->f2 = open(input->av[input->ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (input->f2 < 0)
		input->exit = ERR_FDO2;
	input->limiter = ft_strjoin(input->av[2], "\n");
	if (parse_envp(&(input->cmd1), input->envp, input) != EXIT_SUCCESS)
		free_and_exit(input, input->access);
	if (parse_envp(&(input->cmd2), input->envp, input) != EXIT_SUCCESS)
		free_and_exit(input, input->access);
}
