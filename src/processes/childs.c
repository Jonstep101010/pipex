/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:39:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/06 17:53:22 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

	// print_arr(input->cmd1_args);
/*
 @todo handle errors appropriately
*/
void	child_one(int end[2], t_input *input)
{
	dup2(input->f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(input->f1);
	close(end[1]);
	if (execve((char const *)input->cmd1, input->cmd1_args \
		, input->envp) == -1)
		return (perror("execve child_one"), free_and_exit(input, EXIT_FAILURE));
}

	// print_arr(input->cmd2_args);
void	child_two(int end[2], t_input *input)
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
