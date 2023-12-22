/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:39:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/19 10:17:02 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "structs.h"

void	first_child(int end[2], t_input *input)
{
	if (dup2(input->f1, STDIN_FILENO) == -1)
	{
		free_and_exit(input, 9);
	}
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		free_and_exit(input, 9);
	}
	close(end[0]);
	close(input->f1);
	close(end[1]);
	close(input->f2);
	if (execve((char const *)input->cmd1, input->cmd1_args \
		, input->envp) == -1)
	{
		return (free_and_exit(input, input->exit));
	}
}
		// fprintf(stderr, "execve failed\n");
		// input->error_cmd = input->cmd1_args[0];

void	last_child(int end[2], t_input *input)
{
	close(end[1]);
	close(end[0]);
	if (dup2(input->f2, STDOUT_FILENO) == -1)
	{
		free_and_exit(input, 9);
	}
	close(input->f2);
	if (execve((char const *)input->cmd2, input->cmd2_args \
		, input->envp) == -1)
	{
		return (free_and_exit(input, input->exit));
	}
}
		// perror("dup2: last_child");
		// fprintf(stderr, "execve failed\n");
		// input->error_cmd = input->cmd2_args[0];
