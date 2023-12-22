/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/12/18 17:08:55 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_fork(t_input *input, t_pipes *s_pipes)
{
	s_pipes->childs.first = fork();
	if (s_pipes->childs.first == -1)
		return (perror("Fork: "));
	else if (s_pipes->childs.first == 0)
	{
		input->error_cmd = input->cmd1;
		if (parse_envp(&(input->cmd1), input->envp, input) != EXIT_SUCCESS)
			free_and_exit(input, input->access);
		first_child(s_pipes->end, input);
		waitpid(s_pipes->childs.first, &input->exit, 0);
	}
}

void	last_fork(t_input *input, t_pipes *s_pipes)
{
	s_pipes->childs.last = fork();
	if (s_pipes->childs.last == -1)
		return (perror("Fork: "));
	else if (s_pipes->childs.last == 0)
	{
		input->error_cmd = input->cmd2;
		if (parse_envp(&(input->cmd2), input->envp, input) != EXIT_SUCCESS)
			free_and_exit(input, input->access);
		last_child(s_pipes->end, input);
		waitpid(s_pipes->childs.last, &input->exit, 0);
	}
}

void	default_parent(t_input *input)
{
	t_pipes	s_pipes;

	pipe(s_pipes.end);
	first_fork(input, &s_pipes);
	dup2(s_pipes.end[0], STDIN_FILENO);
	close_fds(s_pipes.end);
	last_fork(input, &s_pipes);
	close_fds(s_pipes.end);
	waitpid(-1, &input->exit, 0);
}
