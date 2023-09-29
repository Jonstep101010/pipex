/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:39:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/09/29 18:45:47 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
@todo implement path finding for these
@todo handle errors appropriately
*/

void	child_one(int end[2], t_input *input)
{
	// char *const	arguments[] = {input->cmd1, input->cmd1_args, NULL};

	dup2(input->f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(input->f1);
	if (execve((char const *)ft_strjoin("/bin/", input->cmd1), input->cmd1_args \
		, input->envp) == -1)
		return (perror("execve child_one"), exit(EXIT_FAILURE));
	close(end[1]);
}

/*
@follow-up implement multiple arguments to a cmd*/
void	child_two(int end[2], t_input *input)
{
	char *const	arguments[] = {input->cmd2, input->cmd2_args, NULL};

	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	dup2(input->f2, STDOUT_FILENO);
	close(end[0]);
	close(input->f2);
	if (execve((char const *)ft_strjoin("/usr/bin/", input->cmd2) \
		, arguments, input->envp) == -1)
		return (perror("execve child_one"), exit(EXIT_FAILURE));
}
