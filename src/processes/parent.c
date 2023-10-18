/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/18 11:36:39 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_pid
{
	pid_t	first;
	pid_t	middle;
	pid_t	last;
}	t_pid;

void	helper_multiple(t_input *input, int end[2], pid_t *middle)
{
	char	**cmdargs;
	int		i;

	cmdargs = NULL;
	i = 3;
	while (i < input->ac - 2)
	{
		cmdargs = parse_args(input->av[i]);
		input->middle = ft_strdup(cmdargs[0]);
		parse_envp(&(input->middle), input->envp);
		pipe(end);
		*middle = fork();
		if (*middle == -1)
			return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
		else if (*middle == 0)
		{
			middle_child(end, input, input->middle, cmdargs);
			waitpid(*middle, &input->exit, 0);
		}
		if (input->exit != EXIT_SUCCESS)
			free_and_exit(input, input->exit);
		if (dup2(end[0], STDIN_FILENO) == -1)
			return (perror("dup2 middle"), free_and_exit(input, EXIT_FAILURE));
		arr_free(cmdargs);
		i++;
		if (i < input->ac - 2)
			close_fds(end);
	}
}

void	parent(t_input *input)
{
	int		end[2];
	t_pid	childs;

	pipe(end);
	childs.first = fork();
	if (childs.first == -1)
		return (perror("Fork: "));
	else if (childs.first == 0)
	{
		parse_envp(&(input->cmd1), input->envp);
		first_child(end, input);
		waitpid(childs.first, &input->exit, 0);
	}
	dup2(end[0], STDIN_FILENO);
	close_fds(end);
	helper_multiple(input, end, &(childs.middle));
	childs.last = fork();
	if (childs.last == -1)
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	else if (childs.last == 0)
	{
		parse_envp(&(input->cmd2), input->envp);
		last_child(end, input);
		waitpid(childs.last, &input->exit, 0);
	}
	close_fds(end);
	waitpid(-1, &input->exit, 0);
}
