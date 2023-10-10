/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:38:37 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/10 18:27:00 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_and_null(void *tofree)
{
	free(tofree);
	tofree = NULL;
}

/**
 * @brief pass in address of string to free
 *
 * @param tofree &str to free
 */
void	free_null_str(char **tofree)
{
	free(*tofree);
	tofree = NULL;
}

void	free_and_exit(t_input *input, int exit_code)
{
	if (input->cmd1)
		free_null_str(&(input->cmd1));
	if (input->cmd2)
		free_null_str(&(input->cmd2));
	if (input->middle)
		free_null_str(&(input->middle));
	if (input->cmd1_args)
		arr_free(input->cmd1_args);
	if (input->cmd2_args)
		arr_free(input->cmd2_args);
	close(input->f1);
	close(input->f2);
	input->envp = NULL;
	exit(exit_code);
}
