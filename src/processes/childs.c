/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:39:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/10 17:48:24 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 @todo work with multiple commands
*/
void	child(int end[2], t_input *input)
{
	dup2(input->f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
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
	// dup2(end[1], STDIN_FILENO);
	// printf("cmd:%s\n", cmd);
	// while (*cmdargs)
	// {
	// 	fprintf(stderr, "p:%s\n", *cmdargs);
	// 	cmdargs++;
	// }
	// close(end[0]);
	if (dup2(end[1], STDOUT_FILENO) == -1)
		return (perror("dup2 failed"), free_and_exit(input, EXIT_FAILURE));
	close(end[1]);
	close(input->f1);
	close(input->f2);
	// perror(cmd);
	if (execve((char const *)cmd, cmdargs \
		, input->envp) == -1)
		return (perror("execve middle:"), free_and_exit(input, EXIT_FAILURE));
	// fprintf(stderr, "executed middle\n");
		// return (perror("execve middle:"));
	// free_null_str(&cmd);
	// arr_free(cmdargs);
}

void	last_child(int end[2], t_input *input)
{
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	dup2(input->f2, STDOUT_FILENO);
	close(end[0]);
	close(input->f2);
	if (execve((char const *)input->cmd2, input->cmd2_args \
		, input->envp) == -1)
		return (perror("execve child_two"), free_and_exit(input, EXIT_FAILURE));
}
