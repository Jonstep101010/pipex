/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/11 11:45:03 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(t_input *input)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;
	pid_t	middle;
	int		i;
	char	**cmdargs;

	pipe(end);
	child1 = fork();
	if (child1 == -1)
		return (perror("Fork: "));
	else if (child1 == 0)
	{
		first_child(end, input);
		waitpid(child1, 0, 0);
	}
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
		middle = fork();
		if (middle == -1)
			return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
		else if (middle == 0)
		{
			middle_child(end, input, input->middle, cmdargs);
			waitpid(middle, 0, 0);
		}
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
	child2 = fork();
	// waitpid(child1, 0, 0);
	if (child2 == -1)
	{
		return (perror("Fork: "), free_and_exit(input, EXIT_FAILURE));
	}
	else if (child2 == 0)
	{
		last_child(end, input);
		waitpid(child2, 0, 0);
	}
	close(end[0]);
	close(end[1]);
	waitpid(-1, 0, 0);
	// while (waitpid(-1, 0, 0) != -1)
	// 	;
}
