/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschwabe <jschwabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:58:27 by jschwabe          #+#    #+#             */
/*   Updated: 2023/10/21 17:34:21 by jschwabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	file_err(char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (true);
}

static void	access_err(char *cmd)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

static void	err_kind(t_input *input, int *exit_code)
{
	if (input->err_fd == ERR_FDO1 && file_err(input->av[1]))
		*exit_code = 0;
	else if (*exit_code == ERR_FDO2 && file_err(input->av[input->ac - 1]))
		*exit_code = 127;
	else if (*exit_code == ERR_F_KO || *exit_code == ERR_X_KO)
	{
		access_err(input->error_cmd);
		if (*exit_code == ERR_F_KO
			&& ft_strncmp(input->error_cmd,
				input->cmd1_args[0],
				ft_strlen(input->error_cmd)) == 0)
			*exit_code = 0;
	}
}

	// if (input->cmd1)
	// 	free_null_str(&(input->cmd1));
	// if (input->cmd2)
	// 	free_null_str(&(input->cmd2));
	// if (input->middle)
	// 	free_null_str(&(input->middle));
void	free_and_exit(t_input *input, int exit_code)
{
	err_kind(input, &(exit_code));
	if (input->cmd1 && *input->cmd1)
		free_null_str(&(input->cmd1));
	if (input->cmd2 && *input->cmd2)
		free_null_str(&(input->cmd2));
	if (input->middle && *input->middle)
		free_null_str(&(input->middle));
	if (input->cmd1_args)
		arr_free(input->cmd1_args);
	if (input->cmd2_args)
		arr_free(input->cmd2_args);
	close(input->f1);
	close(input->f2);
	exit(exit_code);
}
