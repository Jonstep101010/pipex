/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:39:07 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/06 16:03:20 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
@todo implement path finding for these
@todo handle errors appropriately
*/
void	child_one(int end[2], t_input *input)
{
	// print_arr(input->cmd1_args);

	// printf("%s\n", input->cmd1_args[1]);
	dup2(input->f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	close(input->f1);
	close(end[1]);
	if (execve((char const *)input->cmd1, input->cmd1_args \
		, input->envp) == -1)
		return (perror("execve child_one"), free_and_exit(input, EXIT_FAILURE));
}

/*
@follow-up implement multiple arguments to a cmd*/
void	child_two(int end[2], t_input *input)
{
	// print_arr(input->cmd2_args);
	// printf("%s\n", input->cmd2_args[1]);
	// printf("%zu\n", arr_len(input->cmd2_args));
	// char *const	arguments[] = {"awk", "{count++} END {print count}", NULL};
	// printf("%s\n", arguments[1]);
	// ft_printf("%s", input->cmd2);
	dup2(end[0], STDIN_FILENO);
	close(end[1]);
	dup2(input->f2, STDOUT_FILENO);
	close(end[0]);
	close(input->f2);
	if (execve((char const *)input->cmd2, input->cmd2_args \
		, input->envp) == -1)
		return (perror("execve child_two"), free_and_exit(input, EXIT_FAILURE));
}
