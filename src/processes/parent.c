/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:44:23 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/10 18:24:56 by jschwabe         ###   ########.fr       */
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
		child(end, input);
	}
	i = 3;
	cmdargs = NULL;
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	close(end[1]);
		// fprintf(stderr, "cmd:%s\n", input->middle);
	while (i < input->args - 2)
	{
		// dup2(end[1], STDIN_FILENO);
		input->search = true;
		cmdargs = parse_args(input->argv[i]);
		input->middle = ft_strdup(cmdargs[0]);
		// fprintf(stderr, "cmd:%s\n", input->middle);
		// print_arr(cmdargs);
		parse_envp(input, input->envp);
		input->search = false;
		// fprintf(stderr, "cmd:%s\n", input->middle);
		pipe(end);
		middle = fork();
		if (middle == -1)
			return (perror("Fork: "));
		else if (middle == 0)
			middle_child(end, input, input->middle, cmdargs);
		if (dup2(end[0], STDIN_FILENO) == -1)
			perror("dup2 middle");
		arr_free(cmdargs);
		i++;
		if (i < input->args - 2)
		{
			close(end[0]);
			close(end[1]);
		}
	}
	// close(end[0]);
	// close(end[1]);
	child2 = fork();
	if (child2 == -1)
	{
		return (perror("Fork: "));
	}
	else if (child2 == 0)
		last_child(end, input);
	close(end[0]);
	close(end[1]);
	while (waitpid(-1, 0, 0) != -1)
		;
	// waitpid(child1, 0, 0);
	// waitpid(middle, 0, 0);
	// waitpid(-1, 0, 0);
}
