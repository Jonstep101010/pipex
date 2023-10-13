/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/13 09:52:24 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_pid
{
	pid_t	first;
	pid_t	middle;
	pid_t	last;
}	t_pid;

void	parent(t_input *input)
{
	int		end[2];
	t_pid	childs;
	int		i;
	char	**cmdargs;

	pipe(end);
	childs.first = fork();
	if (childs.first == -1)
		return (perror("Fork: "));
	else if (childs.first == 0)
	{
		first_child(end, input);
		waitpid(childs.first, &input->exit, 0);
	}
	// if (input->exit != EXIT_SUCCESS)
	// 	free_and_exit(input, input->exit);
	i = 3;
	cmdargs = NULL;
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
	while (i < input->args - 2)
	{
		input->search = true;
		cmdargs = parse_args(input->argv[i]);
		input->middle = ft_strdup(cmdargs[0]);
		parse_envp(input, input->envp);
		input->search = false;
		pipe(end);
		childs.middle = fork();
		if (childs.middle == -1)
			return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
		else if (childs.middle == 0)
		{
			middle_child(end, input, input->middle, cmdargs);
			waitpid(childs.middle, &input->exit, 0);
		}
		if (input->exit != EXIT_SUCCESS)
			free_and_exit(input, input->exit);
		if (dup2(end[0], STDIN_FILENO) == -1)
			return (perror("dup2 middle"), free_and_exit(input, EXIT_FAILURE));
		arr_free(cmdargs);
		i++;
		if (i < input->args - 2)
		{
			close(end[0]);
			close(end[1]);
		}
	}
	childs.last = fork();
	if (childs.last == -1)
	{
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	}
	else if (childs.last == 0)
	{
		last_child(end, input);
		waitpid(childs.last, &input->exit, 0);
	}
	close(end[0]);
	close(end[1]);
	waitpid(-1, &input->exit, 0);
	// fprintf(stderr, "%d\n", input->exit);
	// while (waitpid(-1, &input->exit, 0) != -1)
	// 	;
}
