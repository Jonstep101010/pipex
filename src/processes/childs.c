/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:39:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 11:27:23 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 @todo work with multiple commands
*/
void	first_child(int end[2], t_input *input)
{
	if (dup2(input->f1, STDIN_FILENO) == -1)
	{
		perror("dup2:1 first_child");
		free_and_exit(input, EXIT_FAILURE);
	}
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		perror("dup2:2 first_child");
		free_and_exit(input, EXIT_FAILURE);
	}
	close(end[0]);
	close(input->f1);
	close(end[1]);
	close(input->f2);
	if (execve((char const *)input->cmd1, input->cmd1_args \
		, input->envp) == -1)
		return (perror("execve child_one"), free_and_exit(input, EXIT_FAILURE));
}

void	middle_child(int end[2], t_input *input, char *cmd, char **cmdargs)
{
	close(end[0]);
	if (dup2(end[1], STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), free_and_exit(input, EXIT_FAILURE));
	close(end[1]);
	close(input->f1);
	close(input->f2);
	if (execve((char const *)cmd, cmdargs \
		, input->envp) == -1)
		return (perror("execve middle:"), free_and_exit(input, EXIT_FAILURE));
}

void	last_child(int end[2], t_input *input)
{
	close(end[1]);
	close(end[0]);
	if (dup2(input->f2, STDOUT_FILENO) == -1)
	{
		perror("dup2: last_child");
		free_and_exit(input, EXIT_FAILURE);
	}
	close(input->f2);
	if (execve((char const *)input->cmd2, input->cmd2_args \
		, input->envp) == -1)
		return (perror("execve last_child"), 
			free_and_exit(input, EXIT_FAILURE));
}
