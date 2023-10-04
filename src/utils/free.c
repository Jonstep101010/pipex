/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:38:37 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/04 17:39:43 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_and_null(void *tofree)
{
	free(tofree);
	tofree = NULL;
}

void	free_and_exit(t_input *input, int exit_code)
{
	if (input->cmd1)
		free_and_null(input->cmd1);
	if (input->cmd2)
		free_and_null(input->cmd2);
	if (input->cmd1_args)
		arr_free(input->cmd1_args);
	if (input->cmd2_args)
		arr_free(input->cmd2_args);
	close(input->f1);
	close(input->f2);
	input->envp = NULL;
	exit(exit_code);
}
