/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 16:03:50 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first_fork(t_input *input, t_pipes *s_pipes)
{
	s_pipes->childs.first = fork();
	if (s_pipes->childs.first == -1)
		return (perror("Fork: "));
	else if (s_pipes->childs.first == 0)
	{
		parse_envp(&(input->cmd1), input->envp);
		first_child(s_pipes->end, input);
		waitpid(s_pipes->childs.first, &input->exit, 0);
	}
}

static void	last_fork(t_input *input, t_pipes *s_pipes)
{
	s_pipes->childs.last = fork();
	if (s_pipes->childs.last == -1)
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	else if (s_pipes->childs.last == 0)
	{
		parse_envp(&(input->cmd2), input->envp);
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

static void	multiple_pipes(t_input *input, t_pipes *s_pipes)
{
	while (s_pipes->i < input->ac - 2)
	{
		s_pipes->cmdargs = parse_args(input->av[s_pipes->i]);
		input->middle = ft_strdup(s_pipes->cmdargs[0]);
		parse_envp(&(input->middle), input->envp);
		pipe(s_pipes->end);
		s_pipes->childs.middle = fork();
		if (s_pipes->childs.middle == -1)
			return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
		else if (s_pipes->childs.middle == 0)
		{
			middle_child(s_pipes->end, input, input->middle, s_pipes->cmdargs);
			waitpid(s_pipes->childs.middle, &input->exit, 0);
		}
		if (input->exit != EXIT_SUCCESS)
			free_and_exit(input, input->exit);
		if (dup2(s_pipes->end[0], STDIN_FILENO) == -1)
			return (perror("dup2 middle"), free_and_exit(input, EXIT_FAILURE));
		arr_free(s_pipes->cmdargs);
		s_pipes->i++;
		if (s_pipes->i < input->ac - 2)
			close_fds(s_pipes->end);
	}
}

void	multiple_parent(t_input *input)
{
	t_pipes	s_pipes;

	s_pipes.i = 3;
	pipe(s_pipes.end);
	first_fork(input, &s_pipes);
	dup2(s_pipes.end[0], STDIN_FILENO);
	close_fds(s_pipes.end);
	multiple_pipes(input, &s_pipes);
	last_fork(input, &s_pipes);
	close_fds(s_pipes.end);
	waitpid(-1, &input->exit, 0);
}
