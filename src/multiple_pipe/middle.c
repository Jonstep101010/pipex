/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:33:00 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/21 17:34:08 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	middle_child(int end[2], t_input *input, char *cmd, char **cmdargs)
{
	close(end[0]);
	if (dup2(end[1], STDOUT_FILENO) == -1)
		return (free_and_exit(input, EXIT_FAILURE));
	close(end[1]);
	close(input->f1);
	close(input->f2);
	if (execve((char const *)cmd, cmdargs \
		, input->envp) == -1)
	{
		return (free_and_exit(input, EXIT_SUCCESS));
	}
}
