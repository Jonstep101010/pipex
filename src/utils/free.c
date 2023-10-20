/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:38:37 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/20 22:36:22 by jschwabe         ###   ########.fr       */
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

	// if (input->cmd1)
	// 	free_null_str(&(input->cmd1));
	// if (input->cmd2)
	// 	free_null_str(&(input->cmd2));
	// if (input->middle)
	// 	free_null_str(&(input->middle));

void	free_and_exit(t_input *input, int exit_code)
{
	// check for NULL?
	if (input->err_fd == ERR_FDO1 || input->err_fd == ERR_FDO1)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(input->av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit_code = 0;
	}
	// else if (input->err_fd == ERR_FDO1)
	// 	exit_code = 127;
	else if (exit_code == ERR_FDO2)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(input->av[input->ac - 1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit_code = 127;
	}
	else if (exit_code == ERR_F_KO)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(input->error_cmd, 2);
		ft_putendl_fd(": command not found", 2);
		// fprintf(stderr, "cmdargs[0]:%s\n", input->cmd1_args[0]);
		if (ft_strncmp(input->error_cmd, input->cmd1_args[0], ft_strlen(input->error_cmd)) == 0)
			exit_code = 0;
	}
	else if (exit_code == ERR_X_KO)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(input->error_cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (input->cmd1_args)
		arr_free(input->cmd1_args);
	if (input->cmd2_args)
		arr_free(input->cmd2_args);
	close(input->f1);
	close(input->f2);
	input->envp = NULL;
	// if (WIFEXITED(input->exit) && WEXITSTATUS(input->exit) == );
	exit(exit_code);
}
